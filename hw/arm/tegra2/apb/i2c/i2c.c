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
#include "hw/i2c/i2c.h"

#include "i2c.h"
#include "iomap.h"
#include "tegra_trace.h"

#define TYPE_TEGRA_I2C "tegra.i2c"
#define TEGRA_I2C(obj) OBJECT_CHECK(tegra_i2c, (obj), TYPE_TEGRA_I2C)
#define DEFINE_REG32(reg) reg##_t reg

typedef struct tegra_i2c_state {
    SysBusDevice parent_obj;

    MemoryRegion iomem;
    I2CBus *bus;
    qemu_irq irq;
    DEFINE_REG32(i2c_i2c_cnfg);
    DEFINE_REG32(i2c_i2c_cmd_addr0);
    DEFINE_REG32(i2c_i2c_cmd_addr1);
    DEFINE_REG32(i2c_i2c_cmd_data1);
    DEFINE_REG32(i2c_i2c_cmd_data2);
    DEFINE_REG32(i2c_i2c_status);
    DEFINE_REG32(i2c_i2c_sl_cnfg);
    DEFINE_REG32(i2c_i2c_sl_rcvd);
    DEFINE_REG32(i2c_i2c_sl_status);
    DEFINE_REG32(i2c_i2c_sl_addr1);
    DEFINE_REG32(i2c_i2c_sl_addr2);
    DEFINE_REG32(i2c_i2c_tlow_sext);
    DEFINE_REG32(i2c_i2c_sl_delay_count);
    DEFINE_REG32(i2c_i2c_sl_int_mask);
    DEFINE_REG32(i2c_i2c_sl_int_source);
    DEFINE_REG32(i2c_i2c_sl_int_set);
    DEFINE_REG32(i2c_i2c_tx_packet_fifo);
    DEFINE_REG32(i2c_i2c_rx_fifo);
    DEFINE_REG32(i2c_i2c_packet_transfer_status);
    DEFINE_REG32(i2c_fifo_control);
    DEFINE_REG32(i2c_fifo_status);
    DEFINE_REG32(i2c_interrupt_mask_register);
    DEFINE_REG32(i2c_interrupt_status_register);
    DEFINE_REG32(i2c_clk_divisor_register);
    DEFINE_REG32(i2c_interrupt_source_register);
    DEFINE_REG32(i2c_i2c_interrupt_set_register);
    DEFINE_REG32(i2c_i2c_slv_tx_packet_fifo);
    DEFINE_REG32(i2c_i2c_slv_rx_fifo);
    DEFINE_REG32(i2c_i2c_slv_packet_status);
} tegra_i2c;

static const VMStateDescription vmstate_tegra_i2c = {
    .name = "tegra.i2c",
    .version_id = 1,
    .fields = (VMStateField[]) {
        VMSTATE_UINT32(i2c_i2c_cnfg.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_cmd_addr0.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_cmd_addr1.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_cmd_data1.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_cmd_data2.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_status.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_cnfg.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_rcvd.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_status.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_addr1.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_addr2.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_tlow_sext.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_delay_count.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_int_mask.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_int_source.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_sl_int_set.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_tx_packet_fifo.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_rx_fifo.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_packet_transfer_status.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_fifo_control.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_fifo_status.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_interrupt_mask_register.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_interrupt_status_register.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_clk_divisor_register.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_interrupt_source_register.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_interrupt_set_register.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_slv_tx_packet_fifo.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_slv_rx_fifo.reg32, tegra_i2c),
        VMSTATE_UINT32(i2c_i2c_slv_packet_status.reg32, tegra_i2c),
        VMSTATE_END_OF_LIST()
    }
};

I2CBus *tegra_i2c_get_bus(void *opaque)
{
    tegra_i2c *s = TEGRA_I2C(opaque);
    return s->bus;
}

static void tegra_i2c_update(tegra_i2c *s, uint32_t it_bit,
                             uint32_t value)
{
    // uint8_t real_mask = s->int_mask |
    //     ((s->header_specific & I2C_HEADER_IE_ENABLE) ? 0x80 : 0);

    // s->int_status = (s->int_status & ~it_bit) | (value ? it_bit : 0);
    // DPRINTF("update 0x%x/0x%x\n", s->int_status, real_mask);

    // if (s->int_status & real_mask) {
    //     qemu_irq_raise(s->irq);
    // } else {
    //     qemu_irq_lower(s->irq);
    // }
}

static uint64_t tegra_i2c_priv_read(void *opaque, hwaddr offset,
                                        unsigned size)
{
    tegra_i2c *s = opaque;
    uint64_t ret = 0;

    switch (offset) {
    case I2C_I2C_CNFG_OFFSET:
        ret = s->i2c_i2c_cnfg.reg32;
        break;
    case I2C_I2C_CMD_ADDR0_OFFSET:
        ret = s->i2c_i2c_cmd_addr0.reg32;
        break;
    case I2C_I2C_CMD_ADDR1_OFFSET:
        ret = s->i2c_i2c_cmd_addr1.reg32;
        break;
    case I2C_I2C_CMD_DATA1_OFFSET:
        ret = s->i2c_i2c_cmd_data1.reg32;
        printf("tegra_i2c_priv_read: reading I2C_CMD_DATA1=0x%x\n", ret);
        break;
    case I2C_I2C_CMD_DATA2_OFFSET:
        ret = s->i2c_i2c_cmd_data2.reg32;
        printf("tegra_i2c_priv_read: reading I2C_CMD_DATA2=0x%x\n", ret);
        break;
    case I2C_I2C_STATUS_OFFSET:
        ret = s->i2c_i2c_status.reg32;
        break;
    case I2C_I2C_SL_CNFG_OFFSET:
        ret = s->i2c_i2c_sl_cnfg.reg32;
        break;
    case I2C_I2C_SL_RCVD_OFFSET:
        ret = s->i2c_i2c_sl_rcvd.reg32;
        break;
    case I2C_I2C_SL_STATUS_OFFSET:
        ret = s->i2c_i2c_sl_status.reg32;
        break;
    case I2C_I2C_SL_ADDR1_OFFSET:
        ret = s->i2c_i2c_sl_addr1.reg32;
        break;
    case I2C_I2C_SL_ADDR2_OFFSET:
        ret = s->i2c_i2c_sl_addr2.reg32;
        break;
    case I2C_I2C_TLOW_SEXT_OFFSET:
        ret = s->i2c_i2c_tlow_sext.reg32;
        break;
    case I2C_I2C_SL_DELAY_COUNT_OFFSET:
        ret = s->i2c_i2c_sl_delay_count.reg32;
        break;
    case I2C_I2C_SL_INT_MASK_OFFSET:
        ret = s->i2c_i2c_sl_int_mask.reg32;
        break;
    case I2C_I2C_SL_INT_SOURCE_OFFSET:
        ret = s->i2c_i2c_sl_int_source.reg32;
        break;
    case I2C_I2C_SL_INT_SET_OFFSET:
        ret = s->i2c_i2c_sl_int_set.reg32;
        break;
    case I2C_I2C_TX_PACKET_FIFO_OFFSET:
        ret = s->i2c_i2c_tx_packet_fifo.reg32;
        break;
    case I2C_I2C_RX_FIFO_OFFSET:
        ret = s->i2c_i2c_rx_fifo.reg32;
        break;
    case I2C_I2C_PACKET_TRANSFER_STATUS_OFFSET:
        ret = s->i2c_i2c_packet_transfer_status.reg32;
        break;
    case I2C_FIFO_CONTROL_OFFSET:
        ret = s->i2c_fifo_control.reg32;
        break;
    case I2C_FIFO_STATUS_OFFSET:
        ret = s->i2c_fifo_status.reg32;
        break;
    case I2C_INTERRUPT_MASK_REGISTER_OFFSET:
        ret = s->i2c_interrupt_mask_register.reg32;
        break;
    case I2C_INTERRUPT_STATUS_REGISTER_OFFSET:
        ret = s->i2c_interrupt_status_register.reg32;
        break;
    case I2C_CLK_DIVISOR_REGISTER_OFFSET:
        ret = s->i2c_clk_divisor_register.reg32;
        break;
    case I2C_INTERRUPT_SOURCE_REGISTER_OFFSET:
        ret = s->i2c_interrupt_source_register.reg32;
        break;
    case I2C_I2C_INTERRUPT_SET_REGISTER_OFFSET:
        ret = s->i2c_i2c_interrupt_set_register.reg32;
        break;
    case I2C_I2C_SLV_TX_PACKET_FIFO_OFFSET:
        ret = s->i2c_i2c_slv_tx_packet_fifo.reg32;
        break;
    case I2C_I2C_SLV_RX_FIFO_OFFSET:
        ret = s->i2c_i2c_slv_rx_fifo.reg32;
        break;
    case I2C_I2C_SLV_PACKET_STATUS_OFFSET:
        ret = s->i2c_i2c_slv_packet_status.reg32;
        break;
    default:
        break;
    }

    TRACE_READ(s->iomem.addr, offset, ret);

    return ret;
}

static void tegra_i2c_priv_write(void *opaque, hwaddr offset,
                                     uint64_t value, unsigned size)
{
    tegra_i2c *s = opaque;
    int ret;

    switch (offset) {
    case I2C_I2C_CNFG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_cnfg.reg32, value);
        s->i2c_i2c_cnfg.reg32 = value;

        if ((s->i2c_i2c_cnfg.send || s->i2c_i2c_cnfg.packet_mode_en) && s->i2c_i2c_cnfg.a_mod) {
            // 10-bit address mode
            printf("tegra_i2c_priv_write: 10-bit address mode\n");
            if (s->i2c_i2c_cmd_addr0.addr0 > 0x1FE) {
                // Real 10-bit address
                printf("tegra_i2c_priv_write: 10-bit addr0 not supported\n");
                break;
            }
            if (s->i2c_i2c_cnfg.slv2 && s->i2c_i2c_cmd_addr1.addr1 > 0x1FE) {
                // Real 10-bit address
                printf("tegra_i2c_priv_write: 10-bit addr1 not supported\n");
                break;
            }
        }

        if (s->i2c_i2c_cnfg.send) {
            printf("tegra_i2c_priv_write: length: %d\n", s->i2c_i2c_cnfg.length + 1);
            printf("tegra_i2c_priv_write: sending to addr0: 0x%x, isRead: %d\n", s->i2c_i2c_cmd_addr0.addr0 >> 1, s->i2c_i2c_cnfg.cmd1);
            ret = i2c_start_transfer(s->bus, s->i2c_i2c_cmd_addr0.addr0 >> 1, s->i2c_i2c_cnfg.cmd1);
            if (ret) {
                // Invalid address
                printf("tegra_i2c_priv_write: invalid addr0: 0x%x\n", s->i2c_i2c_cmd_addr0.addr0 >> 1);
                // s->i2c_i2c_status.cmd1_stat = 1;
            } else {
                if (s->i2c_i2c_cnfg.cmd1) {
                    // read
                    s->i2c_i2c_cmd_data1.reg32 = 0;
                }
                for (unsigned int i = 0; i < s->i2c_i2c_cnfg.length + 1; i++) {
                    if (s->i2c_i2c_cnfg.cmd1) {
                        // read
                        s->i2c_i2c_cmd_data1.reg32 |= i2c_recv(s->bus) << (i * 8);
                        s->i2c_i2c_status.cmd1_stat = 0;
                    } else {
                        // write
                        ret = i2c_send(s->bus, (s->i2c_i2c_cmd_data1.reg32 >> (i * 8)) & 0xFF);
                        if (ret) {
                            // send error
                            printf("tegra_i2c_priv_write: send error for addr0\n");
                            s->i2c_i2c_status.cmd1_stat = i + 1;
                            break;
                        } else {
                            s->i2c_i2c_status.cmd1_stat = 0;
                        }
                    }
                }
                i2c_end_transfer(s->bus);
            }
            if (s->i2c_i2c_cnfg.slv2) {
                printf("tegra_i2c_priv_write: sending to addr1: 0x%x, isRead: %d\n", s->i2c_i2c_cmd_addr1.addr1 >> 1, s->i2c_i2c_cnfg.cmd2);
                ret = i2c_start_transfer(s->bus, s->i2c_i2c_cmd_addr1.addr1 >> 1, s->i2c_i2c_cnfg.cmd2);
                if (ret) {
                    // Invalid address
                    printf("tegra_i2c_priv_write: invalid addr1: 0x%x\n", s->i2c_i2c_cmd_addr1.addr1 >> 1);
                    // s->i2c_i2c_status.cmd2_stat = 1;
                } else {
                    if (s->i2c_i2c_cnfg.cmd2) {
                        // read
                        s->i2c_i2c_cmd_data2.reg32 = 0;
                    }
                    for (unsigned int i = 0; i < s->i2c_i2c_cnfg.length + 1; i++) {
                        if (s->i2c_i2c_cnfg.cmd2) {
                            // read
                            s->i2c_i2c_cmd_data2.reg32 |= i2c_recv(s->bus) << (i * 8);
                            s->i2c_i2c_status.cmd2_stat = 0;
                        } else {
                            // write
                            ret = i2c_send(s->bus, (s->i2c_i2c_cmd_data2.reg32 >> (i * 8)) & 0xFF);
                            if (ret) {
                                // send error
                                printf("tegra_i2c_priv_write: send error for addr1\n");
                                s->i2c_i2c_status.cmd2_stat = i + 1;
                                break;
                            } else {
                                s->i2c_i2c_status.cmd2_stat = 0;
                            }
                        }
                    }
                    i2c_end_transfer(s->bus);
                }
            }
            s->i2c_i2c_cnfg.send = 0;
        }

        if (s->i2c_i2c_cnfg.packet_mode_en) {
            // TO DO
            printf("tegra_i2c_priv_write: packet mode not supported yet!\n");
        }

        break;
    case I2C_I2C_CMD_ADDR0_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_cmd_addr0.reg32, value);
        s->i2c_i2c_cmd_addr0.reg32 = value;
        break;
    case I2C_I2C_CMD_ADDR1_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_cmd_addr1.reg32, value);
        s->i2c_i2c_cmd_addr1.reg32 = value;
        break;
    case I2C_I2C_CMD_DATA1_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_cmd_data1.reg32, value);
        s->i2c_i2c_cmd_data1.reg32 = value;
        break;
    case I2C_I2C_CMD_DATA2_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_cmd_data2.reg32, value);
        s->i2c_i2c_cmd_data2.reg32 = value;
        break;
    case I2C_I2C_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_status.reg32, value);
        // read-only
        break;
    case I2C_I2C_SL_CNFG_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_cnfg.reg32, value);
        s->i2c_i2c_sl_cnfg.reg32 = value;
        break;
    case I2C_I2C_SL_RCVD_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_rcvd.reg32, value);
        s->i2c_i2c_sl_rcvd.reg32 = value;
        break;
    case I2C_I2C_SL_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_status.reg32, value);
        s->i2c_i2c_sl_status.reg32 = value;
        break;
    case I2C_I2C_SL_ADDR1_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_addr1.reg32, value);
        s->i2c_i2c_sl_addr1.reg32 = value;
        break;
    case I2C_I2C_SL_ADDR2_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_addr2.reg32, value);
        s->i2c_i2c_sl_addr2.reg32 = value;
        break;
    case I2C_I2C_TLOW_SEXT_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_tlow_sext.reg32, value);
        s->i2c_i2c_tlow_sext.reg32 = value;
        break;
    case I2C_I2C_SL_DELAY_COUNT_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_delay_count.reg32, value);
        s->i2c_i2c_sl_delay_count.reg32 = value;
        break;
    case I2C_I2C_SL_INT_MASK_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_int_mask.reg32, value);
        s->i2c_i2c_sl_int_mask.reg32 = value;
        break;
    case I2C_I2C_SL_INT_SOURCE_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_int_source.reg32, value);
        s->i2c_i2c_sl_int_source.reg32 = value;
        break;
    case I2C_I2C_SL_INT_SET_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_sl_int_set.reg32, value);
        s->i2c_i2c_sl_int_set.reg32 = value;
        break;
    case I2C_I2C_TX_PACKET_FIFO_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_tx_packet_fifo.reg32, value);
        s->i2c_i2c_tx_packet_fifo.reg32 = value;
        break;
    case I2C_I2C_RX_FIFO_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_rx_fifo.reg32, value);
        s->i2c_i2c_rx_fifo.reg32 = value;
        break;
    case I2C_I2C_PACKET_TRANSFER_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_packet_transfer_status.reg32, value);
        s->i2c_i2c_packet_transfer_status.reg32 = value;
        break;
    case I2C_FIFO_CONTROL_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_fifo_control.reg32, value);
        s->i2c_fifo_control.reg32 = value;

        if (s->i2c_fifo_control.rx_fifo_flush) {

            s->i2c_fifo_control.rx_fifo_flush = 0;
        }

        if (s->i2c_fifo_control.tx_fifo_flush) {
            
            s->i2c_fifo_control.tx_fifo_flush = 0;
        }

        break;
    case I2C_FIFO_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_fifo_status.reg32, value);
        s->i2c_fifo_status.reg32 = value;
        break;
    case I2C_INTERRUPT_MASK_REGISTER_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_interrupt_mask_register.reg32, value);
        s->i2c_interrupt_mask_register.reg32 = value;
        tegra_i2c_update(s, 0, 0);
        break;
    case I2C_INTERRUPT_STATUS_REGISTER_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_interrupt_status_register.reg32, value);
        s->i2c_interrupt_status_register.reg32 &= ~value;
        tegra_i2c_update(s, 0, 0);
        break;
    case I2C_CLK_DIVISOR_REGISTER_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_clk_divisor_register.reg32, value);
        s->i2c_clk_divisor_register.reg32 = value;
        break;
    case I2C_INTERRUPT_SOURCE_REGISTER_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_interrupt_source_register.reg32, value);
        s->i2c_interrupt_source_register.reg32 = value;
        break;
    case I2C_I2C_INTERRUPT_SET_REGISTER_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_interrupt_set_register.reg32, value);
        s->i2c_i2c_interrupt_set_register.reg32 |= value;
        break;
    case I2C_I2C_SLV_TX_PACKET_FIFO_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_slv_tx_packet_fifo.reg32, value);
        s->i2c_i2c_slv_tx_packet_fifo.reg32 = value;
        break;
    case I2C_I2C_SLV_RX_FIFO_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_slv_rx_fifo.reg32, value);
        s->i2c_i2c_slv_rx_fifo.reg32 = value;
        break;
    case I2C_I2C_SLV_PACKET_STATUS_OFFSET:
        TRACE_WRITE(s->iomem.addr, offset, s->i2c_i2c_slv_packet_status.reg32, value);
        s->i2c_i2c_slv_packet_status.reg32 = value;
        break;
    default:
        TRACE_WRITE(s->iomem.addr, offset, 0, value);
        break;
    }
}

static void tegra_i2c_priv_reset(DeviceState *dev)
{
    tegra_i2c *s = TEGRA_I2C(dev);

    s->i2c_i2c_cnfg.reg32 = I2C_I2C_CNFG_RESET;
    s->i2c_i2c_cmd_addr0.reg32 = I2C_I2C_CMD_ADDR0_RESET;
    s->i2c_i2c_cmd_addr1.reg32 = I2C_I2C_CMD_ADDR1_RESET;
    s->i2c_i2c_cmd_data1.reg32 = I2C_I2C_CMD_DATA1_RESET;
    s->i2c_i2c_cmd_data2.reg32 = I2C_I2C_CMD_DATA2_RESET;
    s->i2c_i2c_status.reg32 = I2C_I2C_STATUS_RESET;
    s->i2c_i2c_sl_cnfg.reg32 = I2C_I2C_SL_CNFG_RESET;
    s->i2c_i2c_sl_rcvd.reg32 = I2C_I2C_SL_RCVD_RESET;
    s->i2c_i2c_sl_status.reg32 = I2C_I2C_SL_STATUS_RESET;
    s->i2c_i2c_sl_addr1.reg32 = I2C_I2C_SL_ADDR1_RESET;
    s->i2c_i2c_sl_addr2.reg32 = I2C_I2C_SL_ADDR2_RESET;
    s->i2c_i2c_tlow_sext.reg32 = I2C_I2C_TLOW_SEXT_RESET;
    s->i2c_i2c_sl_delay_count.reg32 = I2C_I2C_SL_DELAY_COUNT_RESET;
    s->i2c_i2c_sl_int_mask.reg32 = I2C_I2C_SL_INT_MASK_RESET;
    s->i2c_i2c_sl_int_source.reg32 = I2C_I2C_SL_INT_SOURCE_RESET;
    s->i2c_i2c_sl_int_set.reg32 = I2C_I2C_SL_INT_SET_RESET;
    s->i2c_i2c_tx_packet_fifo.reg32 = I2C_I2C_TX_PACKET_FIFO_RESET;
    s->i2c_i2c_rx_fifo.reg32 = I2C_I2C_RX_FIFO_RESET;
    s->i2c_i2c_packet_transfer_status.reg32 = I2C_I2C_PACKET_TRANSFER_STATUS_RESET;
    s->i2c_fifo_control.reg32 = I2C_FIFO_CONTROL_RESET;
    s->i2c_fifo_status.reg32 = I2C_FIFO_STATUS_RESET;
    s->i2c_interrupt_mask_register.reg32 = I2C_INTERRUPT_MASK_REGISTER_RESET;
    s->i2c_interrupt_status_register.reg32 = I2C_INTERRUPT_STATUS_REGISTER_RESET;
    s->i2c_clk_divisor_register.reg32 = I2C_CLK_DIVISOR_REGISTER_RESET;
    s->i2c_interrupt_source_register.reg32 = I2C_INTERRUPT_SOURCE_REGISTER_RESET;
    s->i2c_i2c_interrupt_set_register.reg32 = I2C_I2C_INTERRUPT_SET_REGISTER_RESET;
    s->i2c_i2c_slv_tx_packet_fifo.reg32 = I2C_I2C_SLV_TX_PACKET_FIFO_RESET;
    s->i2c_i2c_slv_rx_fifo.reg32 = I2C_I2C_SLV_RX_FIFO_RESET;
    s->i2c_i2c_slv_packet_status.reg32 = I2C_I2C_SLV_PACKET_STATUS_RESET;
}

static const MemoryRegionOps tegra_i2c_mem_ops = {
    .read = tegra_i2c_priv_read,
    .write = tegra_i2c_priv_write,
    .endianness = DEVICE_NATIVE_ENDIAN,
};

static void tegra_i2c_priv_realize(DeviceState *dev, Error **errp)
{
    tegra_i2c *s = TEGRA_I2C(dev);

    sysbus_init_irq(SYS_BUS_DEVICE(dev), &s->irq);

    memory_region_init_io(&s->iomem, OBJECT(dev), &tegra_i2c_mem_ops, s,
                          "tegra.i2c", TEGRA_I2C_SIZE);
    sysbus_init_mmio(SYS_BUS_DEVICE(dev), &s->iomem);

    s->bus = i2c_init_bus(DEVICE(dev), "i2c");
}

static void tegra_i2c_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);

    device_class_set_legacy_reset(dc, tegra_i2c_priv_reset);
    dc->realize = tegra_i2c_priv_realize;
    dc->vmsd = &vmstate_tegra_i2c;
}

static const TypeInfo tegra_i2c_info = {
    .name = TYPE_TEGRA_I2C,
    .parent = TYPE_SYS_BUS_DEVICE,
    .instance_size = sizeof(tegra_i2c),
    .class_init = tegra_i2c_class_init,
};

static void tegra_i2c_register_types(void)
{
    type_register_static(&tegra_i2c_info);
}

type_init(tegra_i2c_register_types)
