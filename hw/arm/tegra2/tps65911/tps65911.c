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

#include "hw/i2c/i2c.h"

#include "tps65911.h"
#include "iomap.h"
#include "trace.h"

#define TYPE_TPS65911 "tps65911"
#define TPS65911(obj) OBJECT_CHECK(tps65911, (obj), TYPE_TPS65911)
#define DEFINE_REG32(reg) reg##_t reg

typedef struct tps65911_state {
    I2CSlave i2c;

    uint8_t ptr;
    uint8_t buf;
    uint8_t len;
    qemu_irq irq;

    // DEFINE_REG32(snor_config);
    // DEFINE_REG32(snor_sta);
    // DEFINE_REG32(snor_nor_addr_ptr);
    // DEFINE_REG32(snor_ahb_addr_ptr);
    // DEFINE_REG32(snor_timing0);
    // DEFINE_REG32(snor_timing1);
    // DEFINE_REG32(snor_mio_cfg);
    // DEFINE_REG32(snor_mio_timing0);
    // DEFINE_REG32(snor_dma_cfg);
    // DEFINE_REG32(snor_cs_mux_cfg);
} tps65911;

static const VMStateDescription vmstate_tps65911 = {
    .name = "tps65911",
    .version_id = 1,
    .fields = (VMStateField[]) {
        // VMSTATE_UINT32(snor_config.reg32, tps65911),
        VMSTATE_END_OF_LIST()
    }
};

// static uint64_t tps65911_read(void *opaque, hwaddr offset,
//                                         unsigned size)
// {
//     tps65911 *s = opaque;
//     uint64_t ret = 0;

//     switch (offset) {
//     case SNOR_CONFIG_OFFSET:
//         ret = s->snor_config.reg32;
//         break;
//     case SNOR_STA_OFFSET:
//         ret = s->snor_sta.reg32;
//         break;
//     case SNOR_NOR_ADDR_PTR_OFFSET:
//         ret = s->snor_nor_addr_ptr.reg32;
//         break;
//     case SNOR_AHB_ADDR_PTR_OFFSET:
//         ret = s->snor_ahb_addr_ptr.reg32;
//         break;
//     case SNOR_TIMING0_OFFSET:
//         ret = s->snor_timing0.reg32;
//         break;
//     case SNOR_TIMING1_OFFSET:
//         ret = s->snor_timing1.reg32;
//         break;
//     case SNOR_MIO_CFG_OFFSET:
//         ret = s->snor_mio_cfg.reg32;
//         break;
//     case SNOR_MIO_TIMING0_OFFSET:
//         ret = s->snor_mio_timing0.reg32;
//         break;
//     case SNOR_DMA_CFG_OFFSET:
//         ret = s->snor_dma_cfg.reg32;
//         break;
//     case SNOR_CS_MUX_CFG_OFFSET:
//         ret = s->snor_cs_mux_cfg.reg32;
//         break;
//     default:
//         break;
//     }

//     TRACE_READ(s->iomem.addr, offset, ret);

//     return ret;
// }

// static void tps65911_write(void *opaque, hwaddr offset,
//                                      uint64_t value, unsigned size)
// {
//     tps65911 *s = opaque;

//     switch (offset) {
//     case SNOR_CONFIG_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_config.reg32, value);
//         s->snor_config.reg32 = value;
//         break;
//     case SNOR_STA_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_sta.reg32, value);
//         s->snor_sta.reg32 = value;
//         break;
//     case SNOR_NOR_ADDR_PTR_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_nor_addr_ptr.reg32, value);
//         s->snor_nor_addr_ptr.reg32 = value;
//         break;
//     case SNOR_AHB_ADDR_PTR_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_ahb_addr_ptr.reg32, value);
//         s->snor_ahb_addr_ptr.reg32 = value;
//         break;
//     case SNOR_TIMING0_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_timing0.reg32, value);
//         s->snor_timing0.reg32 = value;
//         break;
//     case SNOR_TIMING1_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_timing1.reg32, value);
//         s->snor_timing1.reg32 = value;
//         break;
//     case SNOR_MIO_CFG_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_mio_cfg.reg32, value);
//         s->snor_mio_cfg.reg32 = value;
//         break;
//     case SNOR_MIO_TIMING0_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_mio_timing0.reg32, value);
//         s->snor_mio_timing0.reg32 = value;
//         break;
//     case SNOR_DMA_CFG_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_dma_cfg.reg32, value);
//         s->snor_dma_cfg.reg32 = value;
//         break;
//     case SNOR_CS_MUX_CFG_OFFSET:
//         TRACE_WRITE(s->iomem.addr, offset, s->snor_cs_mux_cfg.reg32, value);
//         s->snor_cs_mux_cfg.reg32 = value;
//         break;
//     default:
//         TRACE_WRITE(s->iomem.addr, offset, 0, value);
//         break;
//     }
// }

static void tps65911_read(tps65911 *s)
{
    printf("tps65911_read: len=%d, ptr=0x%02x\n", s->len, s->ptr);
    if (s->len != 1) return;

    switch (s->ptr) {
        case 0x21: // VDD1_REG
            s->buf = (0x3 < 2);
            break;
        case 0x27: // VDDCRTL_REG
            s->buf = 0x0;
            break;
        case 0x28: // VDDCRTL_OP_REG
            s->buf = 0x0;
            break;
        case 0x30: // LDO1_REG
            s->buf = 0x0;
            break;
        case 0x3e: // DCDCCTRL_REG
            s->buf = (1 << 0) | (1 << 3) | (1 << 4) | (1 << 5);
            break;
        case 0x3f: // DEVCTRL_REG
            s->buf = (1 << 4);
            break;
        case 0x40: // DEVCTRL2_REG
            s->buf = (1 << 2) | (0x3 << 4);
            break;
        case 0x6a: // VMBCH_REG
            s->buf = (0x10 << 1); // has to be either 0x20, 0x1e, 0x22, 0x24, 0x28 or 0x2a
            break;
        default:
            printf("tps65911_read: unexpected register 0x%02x\n", s->ptr);
            break;
    }

    s->len = 0;
}

static void tps65911_write(tps65911 *s)
{
    printf("tps65911_write: len=%d\n", s->len);
    if (s->len != 2) return;

    switch (s->ptr) {
        case 0x21: // VDD1_REG
            printf("tps65911_write: 0x21 = 0x%02x\n", s->buf);
            break;
        case 0x27: // VDDCRTL_REG
            printf("tps65911_write: 0x27 = 0x%02x\n", s->buf);
            break;
        case 0x28: // VDDCRTL_OP_REG
            printf("tps65911_write: 0x28 = 0x%02x\n", s->buf);
            break;
        case 0x29: // VDDCRTL_SR_REG
            printf("tps65911_write: 0x29 = 0x%02x\n", s->buf);
            break;
        case 0x3e: // DCDCCTRL_REG
            printf("tps65911_write: 0x3e = 0x%02x\n", s->buf);
            break;
        case 0x3f: // DEVCTRL_REG
            printf("tps65911_write: 0x3f = 0x%02x\n", s->buf);
            break;
        case 0x40: // DEVCTRL2_REG
            printf("tps65911_write: 0x40 = 0x%02x\n", s->buf);
            break;
        case 0x61: // GPIO1_REG
            printf("tps65911_write: 0x61 = 0x%02x\n", s->buf);
            break;
        default:
        printf("tps65911_write: unexpected register 0x%02x\n", s->ptr);
    }
    
    s->len = 0;
}

static uint8_t tps65911_rx(I2CSlave *i2c)
{
    tps65911 *s = TPS65911(i2c);

    printf("tps65911_rx: len=%d, buf=0x%02x\n", s->len, s->buf);

    if (s->len < 1) {
        return s->buf;
    } else {
        printf("tps65911_rx: unexpected data\n");
        return 0;
    }
}

static int tps65911_tx(I2CSlave *i2c, uint8_t data)
{
    tps65911 *s = TPS65911(i2c);

    printf("tps65911_tx: data=0x%02x, len=%d\n", data, s->len);

    switch (s->len) {
        case 0:
            s->ptr = data;
            s->len++;
            break;
        case 1:
            s->buf = data;
            s->len++;
            tps65911_write(s);
            break;
        default:
            printf("tps65911_tx: unexpected data 0x%02x\n", data);
            break;
    }

    return 0;
}

static int tps65911_event(I2CSlave *i2c, enum i2c_event event)
{
    tps65911 *s = TPS65911(i2c);

    printf("tps65911_event: event=%d\n", event);

    if (event == I2C_START_RECV) {
        tps65911_read(s);
    }
    
    return 0;
}

static void tps65911_reset(DeviceState *dev)
{
    tps65911 *s = TPS65911(dev);

    // s->snor_config.reg32 = SNOR_CONFIG_RESET;
    // s->snor_sta.reg32 = SNOR_STA_RESET;
    // s->snor_nor_addr_ptr.reg32 = SNOR_NOR_ADDR_PTR_RESET;
    // s->snor_ahb_addr_ptr.reg32 = SNOR_AHB_ADDR_PTR_RESET;
    // s->snor_timing0.reg32 = SNOR_TIMING0_RESET;
    // s->snor_timing1.reg32 = SNOR_TIMING1_RESET;
    // s->snor_mio_cfg.reg32 = SNOR_MIO_CFG_RESET;
    // s->snor_mio_timing0.reg32 = SNOR_MIO_TIMING0_RESET;
    // s->snor_dma_cfg.reg32 = SNOR_DMA_CFG_RESET;
    // s->snor_cs_mux_cfg.reg32 = SNOR_CS_MUX_CFG_RESET;
}

static void tps65911_realize(DeviceState *dev, Error **errp)
{
    tps65911 *s = TPS65911(dev);


}

static void tps65911_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    I2CSlaveClass *k = I2C_SLAVE_CLASS(klass);

    device_class_set_legacy_reset(dc, tps65911_reset);
    dc->realize = tps65911_realize;
    k->event = tps65911_event;
    k->recv = tps65911_rx;
    k->send = tps65911_tx;
    dc->vmsd = &vmstate_tps65911;
}

static const TypeInfo tps65911_info = {
    .name = TYPE_TPS65911,
    .parent = TYPE_I2C_SLAVE,
    .instance_size = sizeof(tps65911),
    .class_init = tps65911_class_init,
};

static void tps65911_register_types(void)
{
    type_register_static(&tps65911_info);
}

type_init(tps65911_register_types)
