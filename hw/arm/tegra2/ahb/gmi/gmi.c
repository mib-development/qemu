/*
 * ARM NVIDIA Tegra2 emulation.
 *
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

#include "gmi.h"
#include "iomap.h"
#include "tegra_trace.h"

#define TYPE_TEGRA_GMI "tegra.gmi"
#define TEGRA_GMI(obj) OBJECT_CHECK(tegra_gmi, (obj), TYPE_TEGRA_GMI)
#define DEFINE_REG32(reg) reg##_t reg

typedef struct tegra_gmi_state {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    qemu_irq irq;
    DEFINE_REG32(snor_config);
    DEFINE_REG32(snor_sta);
    DEFINE_REG32(snor_nor_addr_ptr);
    DEFINE_REG32(snor_ahb_addr_ptr);
    DEFINE_REG32(snor_timing0);
    DEFINE_REG32(snor_timing1);
    DEFINE_REG32(snor_mio_cfg);
    DEFINE_REG32(snor_mio_timing0);
    DEFINE_REG32(snor_dma_cfg);
    DEFINE_REG32(snor_cs_mux_cfg);
} tegra_gmi;

static const VMStateDescription vmstate_tegra_gmi = {
    .name = "tegra.gmi",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(snor_config.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_sta.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_nor_addr_ptr.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_ahb_addr_ptr.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_timing0.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_timing1.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_mio_cfg.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_mio_timing0.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_dma_cfg.reg32, tegra_gmi),
        VMSTATE_UINT32(snor_cs_mux_cfg.reg32, tegra_gmi),
        VMSTATE_END_OF_LIST()
    }
};

static uint64_t tegra_gmi_priv_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    tegra_gmi *s = opaque;
    uint64_t ret = 0;

    switch (offset) {
    case SNOR_CONFIG_OFFSET:
        ret = s->snor_config.reg32;
        break;
    case SNOR_STA_OFFSET:
        ret = s->snor_sta.reg32;
        break;
    case SNOR_NOR_ADDR_PTR_OFFSET:
        ret = s->snor_nor_addr_ptr.reg32;
        break;
    case SNOR_AHB_ADDR_PTR_OFFSET:
        ret = s->snor_ahb_addr_ptr.reg32;
        break;
    case SNOR_TIMING0_OFFSET:
        ret = s->snor_timing0.reg32;
        break;
    case SNOR_TIMING1_OFFSET:
        ret = s->snor_timing1.reg32;
        break;
    case SNOR_MIO_CFG_OFFSET:
        ret = s->snor_mio_cfg.reg32;
        break;
    case SNOR_MIO_TIMING0_OFFSET:
        ret = s->snor_mio_timing0.reg32;
        break;
    case SNOR_DMA_CFG_OFFSET:
        ret = s->snor_dma_cfg.reg32;
        break;
    case SNOR_CS_MUX_CFG_OFFSET:
        ret = s->snor_cs_mux_cfg.reg32;
        break;
    default:
        break;
    }

    TRACE_READ(s->iomem.addr, offset, ret);

    return ret;
}

static void tegra_gmi_priv_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    tegra_gmi *s = opaque;

    switch (offset) {
    case SNOR_CONFIG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_config.reg32, value);
        s->snor_config.reg32 = value;
        break;
    case SNOR_STA_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_sta.reg32, value);
        s->snor_sta.reg32 = value;
        break;
    case SNOR_NOR_ADDR_PTR_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_nor_addr_ptr.reg32, value);
        s->snor_nor_addr_ptr.reg32 = value;
        break;
    case SNOR_AHB_ADDR_PTR_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_ahb_addr_ptr.reg32, value);
        s->snor_ahb_addr_ptr.reg32 = value;
        break;
    case SNOR_TIMING0_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_timing0.reg32, value);
        s->snor_timing0.reg32 = value;
        break;
    case SNOR_TIMING1_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_timing1.reg32, value);
        s->snor_timing1.reg32 = value;
        break;
    case SNOR_MIO_CFG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_mio_cfg.reg32, value);
        s->snor_mio_cfg.reg32 = value;
        break;
    case SNOR_MIO_TIMING0_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_mio_timing0.reg32, value);
        s->snor_mio_timing0.reg32 = value;
        break;
    case SNOR_DMA_CFG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_dma_cfg.reg32, value);
        s->snor_dma_cfg.reg32 = value;
        break;
    case SNOR_CS_MUX_CFG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->snor_cs_mux_cfg.reg32, value);
        s->snor_cs_mux_cfg.reg32 = value;
        break;
    default:
        TRACE_WRITE(s->iomem.addr, offset, 0, value);
        break;
    }
}

static void tegra_gmi_priv_reset(DeviceState *dev)
{
    tegra_gmi *s = TEGRA_GMI(dev);

    s->snor_config.reg32 = SNOR_CONFIG_RESET;
    s->snor_sta.reg32 = SNOR_STA_RESET;
    s->snor_nor_addr_ptr.reg32 = SNOR_NOR_ADDR_PTR_RESET;
    s->snor_ahb_addr_ptr.reg32 = SNOR_AHB_ADDR_PTR_RESET;
    s->snor_timing0.reg32 = SNOR_TIMING0_RESET;
    s->snor_timing1.reg32 = SNOR_TIMING1_RESET;
    s->snor_mio_cfg.reg32 = SNOR_MIO_CFG_RESET;
    s->snor_mio_timing0.reg32 = SNOR_MIO_TIMING0_RESET;
    s->snor_dma_cfg.reg32 = SNOR_DMA_CFG_RESET;
    s->snor_cs_mux_cfg.reg32 = SNOR_CS_MUX_CFG_RESET;
}

static const MemoryRegionOps tegra_gmi_mem_ops = {
    .read = tegra_gmi_priv_read,
    .write = tegra_gmi_priv_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void tegra_gmi_priv_realize(DeviceState *dev, Error **errp)
{
    tegra_gmi *s = TEGRA_GMI(dev);

    sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->irq);

    memory_region_init_io(&s->iomem, OBJECT(dev), &tegra_gmi_mem_ops, s,
                          "tegra.gmi", TEGRA_SNOR_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);
}

static void tegra_gmi_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    device_class_set_legacy_reset(dc, tegra_gmi_priv_reset);
    dc->realize = tegra_gmi_priv_realize;
    dc->vmsd = &vmstate_tegra_gmi;
}

static const TypeInfo tegra_gmi_info = {
    .name = TYPE_TEGRA_GMI,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(tegra_gmi),
    .class_init = tegra_gmi_class_init,
};

static void tegra_gmi_register_types(void)
{
    type_register_static(&tegra_gmi_info);
}

type_init(tegra_gmi_register_types)
