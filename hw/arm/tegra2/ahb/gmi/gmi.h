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


#ifndef TEGRA_GMI_H
#define TEGRA_GMI_H

#define SNOR_CONFIG_OFFSET 0x0
#define SNOR_CONFIG_RESET  0x10800000
typedef union snor_config_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_config_t;

#define SNOR_STA_OFFSET 0x4
#define SNOR_STA_RESET  0x00000000
typedef union snor_sta_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_sta_t;

#define SNOR_NOR_ADDR_PTR_OFFSET 0x8
#define SNOR_NOR_ADDR_PTR_RESET  0x00000000
typedef union snor_nor_addr_ptr_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_nor_addr_ptr_t;

#define SNOR_AHB_ADDR_PTR_OFFSET 0xC
#define SNOR_AHB_ADDR_PTR_RESET  0x00000000
typedef union snor_ahb_addr_ptr_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_ahb_addr_ptr_t;

#define SNOR_TIMING0_OFFSET 0x10
#define SNOR_TIMING0_RESET  0x30101114
typedef union snor_timing0_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_timing0_t;

#define SNOR_TIMING1_OFFSET 0x14
#define SNOR_TIMING1_RESET  0x00010103
typedef union snor_timing1_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_timing1_t;

#define SNOR_MIO_CFG_OFFSET 0x18
#define SNOR_MIO_CFG_RESET  0x00000107
typedef union snor_mio_cfg_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_mio_cfg_t;

#define SNOR_MIO_TIMING0_OFFSET 0x1C
#define SNOR_MIO_TIMING0_RESET  0x01020102
typedef union snor_mio_timing0_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_mio_timing0_t;

#define SNOR_DMA_CFG_OFFSET 0x20
#define SNOR_DMA_CFG_RESET  0x01000000
typedef union snor_dma_cfg_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_dma_cfg_t;

#define SNOR_CS_MUX_CFG_OFFSET 0x24
#define SNOR_CS_MUX_CFG_RESET  0x76543210
typedef union snor_cs_mux_cfg_u {
    struct {
        // TO DO
    };

    uint32_t reg32;
} snor_cs_mux_cfg_t;

#endif // TEGRA_GMI_H
