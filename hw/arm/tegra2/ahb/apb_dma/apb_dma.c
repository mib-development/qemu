/*
 * ARM NVIDIA Tegra2 emulation.
 *
 * Copyright (c) 2014-2015 Dmitry Osipenko <digetx@gmail.com>
 * Copyright (c) 2025 Iscle Gil <albertiscle9@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify it
 *  under the terms of the GNU General Public License as published by the
 *  Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful, but WITHOUT
 *  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 *  for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "tegra_common.h"

#include "hw/sysbus.h"

#include "apb_dma.h"
#include "iomap.h"
#include "tegra_trace.h"

#define MAX_CHANNELS 32

#define TYPE_TEGRA_APB_DMA "tegra.apb_dma"
#define TEGRA_APB_DMA(obj) OBJECT_CHECK(tegra_apb_dma, (obj), TYPE_TEGRA_APB_DMA)
#define DEFINE_REG32(reg) reg##_t reg
#define WR_MASKED(r, d, m)  r = (r & ~m##_WRMASK) | (d & m##_WRMASK)

typedef struct tegra_apb_dma_channel_state {
    qemu_irq irq;
    DEFINE_REG32(channel_csr);
    DEFINE_REG32(channel_sta);
    DEFINE_REG32(channel_dma_byte_sta);
    DEFINE_REG32(channel_ahb_ptr);
    DEFINE_REG32(channel_ahb_seq);
    DEFINE_REG32(channel_apb_ptr);
    DEFINE_REG32(channel_apb_seq);
} tegra_apb_dma_channel;

static const VMStateDescription vmstate_tegra_apb_dma_channel = {
    .name = "tegra.apb_dma.channel",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(channel_csr.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_sta.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_dma_byte_sta.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_ahb_ptr.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_ahb_seq.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_apb_ptr.reg32, tegra_apb_dma_channel),
        VMSTATE_UINT32(channel_apb_seq.reg32, tegra_apb_dma_channel),
        VMSTATE_END_OF_LIST()
    }
};

typedef struct tegra_apb_dma_state {
    /*< private >*/
    SysBusDevice parent_obj;

    /*< public >*/
    MemoryRegion iomem;
    qemu_irq irqs[2];

    DEFINE_REG32(command);
    DEFINE_REG32(status);
    DEFINE_REG32(requestors_tx);
    DEFINE_REG32(requestors_rx);
    DEFINE_REG32(cntrl_reg);
    DEFINE_REG32(irq_sta_cpu);
    DEFINE_REG32(irq_sta_cop);
    DEFINE_REG32(irq_mask);
    DEFINE_REG32(irq_mask_set);
    DEFINE_REG32(irq_mask_clr);
    DEFINE_REG32(trig_reg);
    DEFINE_REG32(channel_trig_reg);
    DEFINE_REG32(dma_status);
    DEFINE_REG32(channel_en_reg);
    tegra_apb_dma_channel channels[MAX_CHANNELS];
} tegra_apb_dma;

static const VMStateDescription vmstate_tegra_apb_dma = {
    .name = "tegra.apb_dma",
    .version_id = 1,
    .minimum_version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(command.reg32, tegra_apb_dma),
        VMSTATE_UINT32(status.reg32, tegra_apb_dma),
        VMSTATE_UINT32(requestors_tx.reg32, tegra_apb_dma),
        VMSTATE_UINT32(requestors_rx.reg32, tegra_apb_dma),
        VMSTATE_UINT32(cntrl_reg.reg32, tegra_apb_dma),
        VMSTATE_UINT32(irq_sta_cpu.reg32, tegra_apb_dma),
        VMSTATE_UINT32(irq_sta_cop.reg32, tegra_apb_dma),
        VMSTATE_UINT32(irq_mask.reg32, tegra_apb_dma),
        VMSTATE_UINT32(irq_mask_set.reg32, tegra_apb_dma),
        VMSTATE_UINT32(irq_mask_clr.reg32, tegra_apb_dma),
        VMSTATE_UINT32(trig_reg.reg32, tegra_apb_dma),
        VMSTATE_UINT32(channel_trig_reg.reg32, tegra_apb_dma),
        VMSTATE_UINT32(dma_status.reg32, tegra_apb_dma),
        VMSTATE_UINT32(channel_en_reg.reg32, tegra_apb_dma),
        VMSTATE_STRUCT_ARRAY(channels, tegra_apb_dma, MAX_CHANNELS, 0,
                             vmstate_tegra_apb_dma_channel, tegra_apb_dma_channel),
        VMSTATE_END_OF_LIST()
    }
};

static inline uint32_t tegra_apb_dma_get_mask(void *opaque)
{
    tegra_apb_dma *s = opaque;

    return s->irq_mask_set.reg32 & ~s->irq_mask_clr.reg32;
}

static void tegra_apb_dma_update_irq(void *opaque)
{
    tegra_apb_dma *s = opaque;
    uint32_t irq_sta_cpu = 0;
    uint32_t irq_sta_cop = 0;
    uint32_t dma_status = 0;

    for (int i = 0; i < MAX_CHANNELS; i++) {
        tegra_apb_dma_channel *channel = &s->channels[i];
        int intr = channel->channel_csr.ie_eoc && channel->channel_sta.ise_eoc;
        
        if (intr) {
            dma_status |= BIT(i);
            if (channel->channel_ahb_seq.intr_enb) {
                irq_sta_cpu |= BIT(i);
            } else {
                irq_sta_cop |= BIT(i);
            }
        }

        qemu_set_irq(channel->irq, intr);
    }

    s->irq_sta_cpu.reg32 = irq_sta_cpu;
    s->irq_sta_cop.reg32 = irq_sta_cop;
    s->dma_status.reg32 = dma_status;

    qemu_set_irq(s->irqs[0], (s->irq_sta_cpu.reg32 & tegra_apb_dma_get_mask(s)) != 0);
    qemu_set_irq(s->irqs[1], (s->irq_sta_cop.reg32 & tegra_apb_dma_get_mask(s)) != 0);
}

static uint64_t tegra_apb_dma_priv_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    tegra_apb_dma *s = opaque;
    uint64_t ret = 0;

    switch (offset) {
    case COMMAND_OFFSET:
        ret = s->command.reg32;
        break;
    case STATUS_OFFSET:
        ret = s->status.reg32;
        break;
    case REQUESTORS_TX_OFFSET:
        ret = s->requestors_tx.reg32;
        break;
    case REQUESTORS_RX_OFFSET:
        ret = s->requestors_rx.reg32;
        break;
    case CNTRL_REG_OFFSET:
        ret = s->cntrl_reg.reg32;
        break;
    case IRQ_STA_CPU_OFFSET:
        ret = s->irq_sta_cpu.reg32 & tegra_apb_dma_get_mask(s);
        break;
    case IRQ_STA_COP_OFFSET:
        ret = s->irq_sta_cop.reg32 & tegra_apb_dma_get_mask(s);
        break;
    case IRQ_MASK_OFFSET:
        ret = s->irq_mask.reg32 & tegra_apb_dma_get_mask(s);
        break;
    case IRQ_MASK_SET_OFFSET:
        ret = s->irq_mask_set.reg32;
        break;
    case IRQ_MASK_CLR_OFFSET:
        ret = s->irq_mask_clr.reg32;
        break;
    case TRIG_REG_OFFSET:
        ret = s->trig_reg.reg32;
        break;
    case CHANNEL_TRIG_REG_OFFSET:
        ret = s->channel_trig_reg.reg32;
        break;
    case DMA_STATUS_OFFSET:
        ret = s->dma_status.reg32;
        break;
    case CHANNEL_EN_REG_OFFSET:
        ret = s->channel_en_reg.reg32;
        break;
    case CHANNEL_CSR_OFFSET...CHANNEL_APB_SEQ_OFFSET * MAX_CHANNELS:
        int channel = (offset - CHANNEL_CSR_OFFSET) / TEGRA_APB_DMA_CH_SIZE;
        int reg = (offset - CHANNEL_CSR_OFFSET) % TEGRA_APB_DMA_CH_SIZE;
        switch (reg) {
        case CHANNEL_CSR_OFFSET:
            ret = s->channels[channel].channel_csr.reg32;
            break;
        case CHANNEL_STA_OFFSET:
            ret = s->channels[channel].channel_sta.reg32;
            break;
        case CHANNEL_DMA_BYTE_STA_OFFSET:
            ret = s->channels[channel].channel_dma_byte_sta.reg32;
            break;
        case CHANNEL_AHB_PTR_OFFSET:
            ret = s->channels[channel].channel_ahb_ptr.reg32;
            break;
        case CHANNEL_AHB_SEQ_OFFSET:
            ret = s->channels[channel].channel_ahb_seq.reg32;
            break;
        case CHANNEL_APB_PTR_OFFSET:
            ret = s->channels[channel].channel_apb_ptr.reg32;
            break;
        case CHANNEL_APB_SEQ_OFFSET:
            ret = s->channels[channel].channel_apb_seq.reg32;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    TRACE_READ(s->iomem.addr, offset, ret);

    return ret;
}

static void tegra_apb_dma_priv_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    tegra_apb_dma *s = opaque;

    switch (offset) {
    case COMMAND_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->command.reg32, value);
        s->command.reg32 = value;
        break;
    case CNTRL_REG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->cntrl_reg.reg32, value);
        s->cntrl_reg.reg32 = value;
        break;
    case IRQ_MASK_SET_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->irq_mask_set.reg32, value);
        s->irq_mask_set.reg32 = value;
        tegra_apb_dma_update_irq(s);
        break;
    case IRQ_MASK_CLR_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->irq_mask_clr.reg32, value);
        s->irq_mask_clr.reg32 = value;
        tegra_apb_dma_update_irq(s);
        break;
    case TRIG_REG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->trig_reg.reg32, value);
        s->trig_reg.reg32 = value;
        break;
    case CHANNEL_TRIG_REG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->channel_trig_reg.reg32, value);
        s->channel_trig_reg.reg32 = value;
        break;
    case CHANNEL_EN_REG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->channel_en_reg.reg32, value);
        s->channel_en_reg.reg32 = value;
        break;
    case CHANNEL_CSR_OFFSET...CHANNEL_APB_SEQ_OFFSET * MAX_CHANNELS:
        int channel_idx = (offset - CHANNEL_CSR_OFFSET) / TEGRA_APB_DMA_CH_SIZE;
        int reg = (offset - CHANNEL_CSR_OFFSET) % TEGRA_APB_DMA_CH_SIZE;
        tegra_apb_dma_channel *channel = &s->channels[channel_idx];

        switch (reg) {
        case CHANNEL_CSR_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_csr.reg32, value);
            channel->channel_csr.reg32 = value;

            if (channel->channel_csr.enb) {
                // TODO
                printf("UNIMPLEMENTED: DMA channel %d enabled\n", channel_idx);
                channel->channel_csr.enb = 0;

                if (channel->channel_csr.ie_eoc) {
                    channel->channel_sta.ise_eoc = 1;
                }
            }
            
            tegra_apb_dma_update_irq(s);
            break;
        case CHANNEL_STA_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_sta.reg32, value & CHANNEL_STA_WRMASK);
            WR_MASKED(channel->channel_sta.reg32, value, CHANNEL_STA);
            
            if (channel->channel_sta.ise_eoc) {
                channel->channel_sta.ise_eoc = 0;
                tegra_apb_dma_update_irq(s);
            }
            break;
        case CHANNEL_DMA_BYTE_STA_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_dma_byte_sta.reg32, value);
            channel->channel_dma_byte_sta.reg32 = value;
            break;
        case CHANNEL_AHB_PTR_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_ahb_ptr.reg32, value);
            channel->channel_ahb_ptr.reg32 = value;
            break;
        case CHANNEL_AHB_SEQ_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_ahb_seq.reg32, value);
            channel->channel_ahb_seq.reg32 = value;
            break;
        case CHANNEL_APB_PTR_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_apb_ptr.reg32, value);
            channel->channel_apb_ptr.reg32 = value;
            break;
        case CHANNEL_APB_SEQ_OFFSET:
            TRACE_WRITE(s->iomem.addr, offset, channel->channel_apb_seq.reg32, value);
            channel->channel_apb_seq.reg32 = value;
            break;
        default:
            break;
        }
        break;
    default:
        TRACE_WRITE(s->iomem.addr, offset, 0, value);
        break;
    }
}

static void tegra_apb_dma_priv_reset(DeviceState *dev)
{
    tegra_apb_dma *s = TEGRA_APB_DMA(dev);

    s->command.reg32 = COMMAND_RESET;
    s->status.reg32 = STATUS_RESET;
    s->requestors_tx.reg32 = REQUESTORS_TX_RESET;
    s->requestors_rx.reg32 = REQUESTORS_RX_RESET;
    s->cntrl_reg.reg32 = CNTRL_REG_RESET;
    s->irq_sta_cpu.reg32 = IRQ_STA_CPU_RESET;
    s->irq_sta_cop.reg32 = IRQ_STA_COP_RESET;
    s->irq_mask.reg32 = IRQ_MASK_RESET;
    s->irq_mask_set.reg32 = IRQ_MASK_SET_RESET;
    s->irq_mask_clr.reg32 = IRQ_MASK_CLR_RESET;
    s->trig_reg.reg32 = TRIG_REG_RESET;
    s->channel_trig_reg.reg32 = CHANNEL_TRIG_REG_RESET;
    s->dma_status.reg32 = DMA_STATUS_RESET;
    s->channel_en_reg.reg32 = CHANNEL_EN_REG_RESET;

    for (int i = 0; i < MAX_CHANNELS; i++) {
        s->channels[i].channel_csr.reg32 = CHANNEL_CSR_RESET;
        s->channels[i].channel_sta.reg32 = CHANNEL_STA_RESET;
        s->channels[i].channel_dma_byte_sta.reg32 = CHANNEL_DMA_BYTE_STA_RESET;
        s->channels[i].channel_ahb_ptr.reg32 = CHANNEL_AHB_PTR_RESET;
        s->channels[i].channel_ahb_seq.reg32 = CHANNEL_AHB_SEQ_RESET;
        s->channels[i].channel_apb_ptr.reg32 = CHANNEL_APB_PTR_RESET;
        s->channels[i].channel_apb_seq.reg32 = CHANNEL_APB_SEQ_RESET;
    }
}

static const MemoryRegionOps tegra_apb_dma_mem_ops = {
    .read = tegra_apb_dma_priv_read,
    .write = tegra_apb_dma_priv_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void tegra_apb_dma_priv_realize(DeviceState *dev, Error **errp)
{
    tegra_apb_dma *s = TEGRA_APB_DMA(dev);

    memory_region_init_io(&s->iomem, OBJECT(dev), &tegra_apb_dma_mem_ops, s,
                          "tegra.apb_dma", TEGRA_APB_DMA_SIZE + TEGRA_APB_DMA_CH_SIZE * MAX_CHANNELS);
    sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);

    for (int i = 0; i < ARRAY_SIZE(s->irqs); i++) {
        sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->irqs[i]);
    }

    for (int i = 0; i < MAX_CHANNELS; i++) {
        sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->channels[i].irq);
    }
}

static void tegra_apb_dma_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    device_class_set_legacy_reset(dc, tegra_apb_dma_priv_reset);
    dc->realize = tegra_apb_dma_priv_realize;
    dc->vmsd = &vmstate_tegra_apb_dma;
}

static const TypeInfo tegra_apb_dma_info = {
    .name = TYPE_TEGRA_APB_DMA,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(tegra_apb_dma),
    .class_init = tegra_apb_dma_class_init,
};

static void tegra_apb_dma_register_types(void)
{
    type_register_static(&tegra_apb_dma_info);
}

type_init(tegra_apb_dma_register_types)
