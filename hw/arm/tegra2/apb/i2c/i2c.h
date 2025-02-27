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


#ifndef TEGRA_I2C_H
#define TEGRA_I2C_H

#define I2C_I2C_CNFG_OFFSET 0x0
#define I2C_I2C_CNFG_RESET  0x00000800
typedef union i2c_i2c_cnfg_u {
    struct {
        unsigned int a_mod:1;
        unsigned int length: 3;
        unsigned int slv2:1;
        unsigned int start:1;
        unsigned int cmd1:1;
        unsigned int cmd2:1;
        unsigned int noack:1;
        unsigned int send:1;
        unsigned int packet_mode_en:1;
        unsigned int new_master_fsm:1;
        unsigned int debounce_cnt:3;
        unsigned int mstr_clr_bu_on_timeout:1;
        unsigned int undefined_bits_16_31:16;
    };

    uint32_t reg32;
} i2c_i2c_cnfg_t;

#define I2C_I2C_CMD_ADDR0_OFFSET 0x4
#define I2C_I2C_CMD_ADDR0_RESET  0x00000000
typedef union i2c_i2c_cmd_addr0_u {
    struct {
        unsigned int addr0:10;
        unsigned int undefined_bits_10_31:22;
    };

    uint32_t reg32;
} i2c_i2c_cmd_addr0_t;

#define I2C_I2C_CMD_ADDR1_OFFSET 0x8
#define I2C_I2C_CMD_ADDR1_RESET  0x00000000
typedef union i2c_i2c_cmd_addr1_u {
    struct {
        unsigned int addr1:10;
        unsigned int undefined_bits_10_31:22;
    };

    uint32_t reg32;
} i2c_i2c_cmd_addr1_t;

#define I2C_I2C_CMD_DATA1_OFFSET 0xC
#define I2C_I2C_CMD_DATA1_RESET  0x00000000
typedef union i2c_i2c_cmd_data1_u {
    struct {
        unsigned int data1:8;
        unsigned int data2:8;
        unsigned int data3:8;
        unsigned int data4:8;
    };

    uint32_t reg32;
} i2c_i2c_cmd_data1_t;

#define I2C_I2C_CMD_DATA2_OFFSET 0x10
#define I2C_I2C_CMD_DATA2_RESET  0x00000000
typedef union i2c_i2c_cmd_data2_u {
    struct {
        unsigned int data5:8;
        unsigned int data6:8;
        unsigned int data7:8;
        unsigned int data8:8;
    };

    uint32_t reg32;
} i2c_i2c_cmd_data2_t;

#define I2C_I2C_STATUS_OFFSET 0x1C
#define I2C_I2C_STATUS_RESET  0x00000000
typedef union i2c_i2c_status_u {
    struct {
        unsigned int cmd1_stat:4;
        unsigned int cmd2_stat:4;
        unsigned int busy:1;
        unsigned int undefined_bits_9_31:23;
    };

    uint32_t reg32;
} i2c_i2c_status_t;

#define I2C_I2C_SL_CNFG_OFFSET 0x20
#define I2C_I2C_SL_CNFG_RESET  0x00000004
typedef union i2c_i2c_sl_cnfg_u {
    struct {
        unsigned int resp:1;
        unsigned int nack:1;
        unsigned int newsl:1;
        unsigned int enable_sl:1;
        unsigned int pkt_mode_en:1;
        unsigned int ack_withhold_en:1;
        unsigned int ack_last_byte:1;
        unsigned int ack_last_byte_valid:1;
        unsigned int buffer_size:12;
        unsigned int fifo_xfer_en:1;
        unsigned int undefined_bits_21_31:11;
    };

    uint32_t reg32;
} i2c_i2c_sl_cnfg_t;

#define I2C_I2C_SL_RCVD_OFFSET 0x24
#define I2C_I2C_SL_RCVD_RESET  0x00000000
typedef union i2c_i2c_sl_rcvd_u {
    struct {
        unsigned int sl_data:8;
        unsigned int undefined_bits_8_31:24;
    };

    uint32_t reg32;
} i2c_i2c_sl_rcvd_t;

#define I2C_I2C_SL_STATUS_OFFSET 0x28
#define I2C_I2C_SL_STATUS_RESET  0x00000000
typedef union i2c_i2c_sl_status_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_status_t;

#define I2C_I2C_SL_ADDR1_OFFSET 0x2C
#define I2C_I2C_SL_ADDR1_RESET  0x00000000
typedef union i2c_i2c_sl_addr1_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_addr1_t;

#define I2C_I2C_SL_ADDR2_OFFSET 0x30
#define I2C_I2C_SL_ADDR2_RESET  0x00000000
typedef union i2c_i2c_sl_addr2_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_addr2_t;

#define I2C_I2C_TLOW_SEXT_OFFSET 0x34
#define I2C_I2C_TLOW_SEXT_RESET  0x00000000
typedef union i2c_i2c_tlow_sext_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_tlow_sext_t;

#define I2C_I2C_SL_DELAY_COUNT_OFFSET 0x3C
#define I2C_I2C_SL_DELAY_COUNT_RESET  0x0000001E
typedef union i2c_i2c_sl_delay_count_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_delay_count_t;

#define I2C_I2C_SL_INT_MASK_OFFSET 0x40
#define I2C_I2C_SL_INT_MASK_RESET  0x000000FD
typedef union i2c_i2c_sl_int_mask_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_int_mask_t;

#define I2C_I2C_SL_INT_SOURCE_OFFSET 0x44
#define I2C_I2C_SL_INT_SOURCE_RESET  0x00000000
typedef union i2c_i2c_sl_int_source_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_int_source_t;

#define I2C_I2C_SL_INT_SET_OFFSET 0x48
#define I2C_I2C_SL_INT_SET_RESET  0x00000000
typedef union i2c_i2c_sl_int_set_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_sl_int_set_t;

#define I2C_I2C_TX_PACKET_FIFO_OFFSET 0x50
#define I2C_I2C_TX_PACKET_FIFO_RESET  0x00000000
typedef union i2c_i2c_tx_packet_fifo_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_tx_packet_fifo_t;

#define I2C_I2C_RX_FIFO_OFFSET 0x54
#define I2C_I2C_RX_FIFO_RESET  0x00000000
typedef union i2c_i2c_rx_fifo_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_rx_fifo_t;

#define I2C_I2C_PACKET_TRANSFER_STATUS_OFFSET 0x58
#define I2C_I2C_PACKET_TRANSFER_STATUS_RESET  0x00000000
typedef union i2c_i2c_packet_transfer_status_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_packet_transfer_status_t;

#define I2C_FIFO_CONTROL_OFFSET 0x5C
#define I2C_FIFO_CONTROL_RESET  0x00000000
typedef union i2c_fifo_control_u {
    struct {
        unsigned int rx_fifo_flush:1;
        unsigned int tx_fifo_flush:1;
        unsigned int rx_fifo_trig:3;
        unsigned int tx_fifo_trig:3;
        unsigned int slv_rx_fifo_flush:1;
        unsigned int slv_tx_fifo_flush:1;
        unsigned int slv_rx_fifo_trig:3;
        unsigned int slv_tx_fifo_trig:3;
        unsigned int undefined_bits_16_31:16;
    };

    uint32_t reg32;
} i2c_fifo_control_t;

#define I2C_FIFO_STATUS_OFFSET 0x60
#define I2C_FIFO_STATUS_RESET  0x00000000
typedef union i2c_fifo_status_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_fifo_status_t;

#define I2C_INTERRUPT_MASK_REGISTER_OFFSET 0x64
#define I2C_INTERRUPT_MASK_REGISTER_RESET  0x00000000
typedef union i2c_interrupt_mask_register_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_interrupt_mask_register_t;

#define I2C_INTERRUPT_STATUS_REGISTER_OFFSET 0x68
#define I2C_INTERRUPT_STATUS_REGISTER_RESET  0x00000000
typedef union i2c_interrupt_status_register_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_interrupt_status_register_t;

#define I2C_CLK_DIVISOR_REGISTER_OFFSET 0x6C
#define I2C_CLK_DIVISOR_REGISTER_RESET  0x00000000
typedef union i2c_clk_divisor_register_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_clk_divisor_register_t;

#define I2C_INTERRUPT_SOURCE_REGISTER_OFFSET 0x70
#define I2C_INTERRUPT_SOURCE_REGISTER_RESET  0x00000000
typedef union i2c_interrupt_source_register_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_interrupt_source_register_t;

#define I2C_I2C_INTERRUPT_SET_REGISTER_OFFSET 0x74
#define I2C_I2C_INTERRUPT_SET_REGISTER_RESET  0x00000000
typedef union i2c_i2c_interrupt_set_register_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_interrupt_set_register_t;

#define I2C_I2C_SLV_TX_PACKET_FIFO_OFFSET 0x78
#define I2C_I2C_SLV_TX_PACKET_FIFO_RESET  0x00000000
typedef union i2c_i2c_slv_tx_packet_fifo_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_slv_tx_packet_fifo_t;

#define I2C_I2C_SLV_RX_FIFO_OFFSET 0x7C
#define I2C_I2C_SLV_RX_FIFO_RESET  0x00000000
typedef union i2c_i2c_slv_rx_fifo_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_slv_rx_fifo_t;

#define I2C_I2C_SLV_PACKET_STATUS_OFFSET 0x80
#define I2C_I2C_SLV_PACKET_STATUS_RESET  0x00000000
typedef union i2c_i2c_slv_packet_status_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} i2c_i2c_slv_packet_status_t;

I2CBus *tegra_i2c_get_bus(void *opaque);

#endif // TEGRA_I2C_H
