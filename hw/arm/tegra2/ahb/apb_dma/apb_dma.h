/*
 * ARM NVIDIA Tegra2 emulation.
 *
 * Copyright (c) 2014-2015 Dmitry Osipenko <digetx@gmail.com>
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

#ifndef TEGRA_APB_DMA_H
#define TEGRA_APB_DMA_H

#define COMMAND_OFFSET 0x0
#define COMMAND_RESET  0x00000000
typedef union command_u {
    struct {
        unsigned int undefined_bits_0_30:31;
        unsigned int gen:1;                 /* Enables Global APB-DMA; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} command_t;

#define STATUS_OFFSET 0x4
#define STATUS_RESET  0x00000000
typedef union status_u {
    struct {
        unsigned int bsy_0:1;               /* DMA channel0 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_1:1;               /* DMA channel1 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_2:1;               /* DMA channel2 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_3:1;               /* DMA channel3 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_4:1;               /* DMA channel4 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_5:1;               /* DMA channel5 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_6:1;               /* DMA channel6 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_7:1;               /* DMA channel7 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_8:1;               /* DMA channel8 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_9:1;               /* DMA channel9 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_10:1;              /* DMA channel10 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_11:1;              /* DMA channel11 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_12:1;              /* DMA channel12 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_13:1;              /* DMA channel13 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_14:1;              /* DMA channel14 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_15:1;              /* DMA channel15 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_16:1;              /* DMA channel16 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_17:1;              /* DMA channel17 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_18:1;              /* DMA channel18 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_19:1;              /* DMA channel19 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_20:1;              /* DMA channel20 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_21:1;              /* DMA channel21 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_22:1;              /* DMA channel22 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_23:1;              /* DMA channel23 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_24:1;              /* DMA channel24 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_25:1;              /* DMA channel25 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_26:1;              /* DMA channel26 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_27:1;              /* DMA channel27 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_28:1;              /* DMA channel28 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_29:1;              /* DMA channel29 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_30:1;              /* DMA channel30 status; 0 = NOT_BUSY; 1 = BUSY */
        unsigned int bsy_31:1;              /* DMA channel31 status; 0 = NOT_BUSY; 1 = BUSY */
    };

    uint32_t reg32;
} status_t;

#define REQUESTORS_TX_OFFSET 0x8
#define REQUESTORS_TX_RESET  0x00000000
typedef union requestors_tx_u {
    struct {
        unsigned int cntr_req:1;            /* 1 = Enable counter request. 0 = Disable counter request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch0:1;           /* APBIF DMA Channel 0; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch1:1;           /* APBIF DMA Channel 1; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch2:1;           /* APBIF DMA Channel 2; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch3:1;           /* APBIF DMA Channel 3; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int hsi:1;                 /* HSI  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_6_7:2;
        unsigned int uart_a:1;              /* UART1  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_b:1;              /* UART2  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_c:1;              /* UART3  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_11_14:4;
        unsigned int sl2b1:1;               /* SLINK 2B-1 (SPI1); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b2:1;               /* SLINK 2B-2 (SPI2); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b3:1;               /* SLINK 2B-3 (SPI3); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b4:1;               /* SLINK 2B-4 (SPI4) 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_d:1;              /* UART4  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_e:1;              /* UART5  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_1:1;               /* I2C1  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_2:1;               /* I2C2  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_3:1;               /* I2C3  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int dvc_i2c:1;             /* DVC-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int owr:1;                 /* OWR-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_4:1;               /* I2C4  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int sl2b5:1;               /* SLINK 2B-5; 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int sl2b6:1;               /* SLINK 2B-6; 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int undefined_bits_29_31:3;
    };

    uint32_t reg32;
} requestors_tx_t;

#define REQUESTORS_RX_OFFSET 0xC
#define REQUESTORS_RX_RESET  0x00000000
typedef union requestors_rx_u {
    struct {
        unsigned int cntr_req:1;            /* indicates Enabled counter request or not; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch0:1;           /* APBIF DMA Channel 0; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch1:1;           /* APBIF DMA Channel 1; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch2:1;           /* APBIF DMA Channel 2; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int apbif_ch3:1;           /* APBIF DMA Channel 3; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int hsi:1;                 /* HSI  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_6_7:2;
        unsigned int uart_a:1;              /* UART1  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_b:1;              /* UART2  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_c:1;              /* UART3  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int spi:1;                 /* SPI/DTV  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_12_14:3;
        unsigned int sl2b1:1;               /* SLINK 2B-1 (SPI1); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b2:1;               /* SLINK 2B-2 (SPI2); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b3:1;               /* SLINK 2B-3 (SPI3); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int sl2b4:1;               /* SLINK 2B-4 (SPI4) 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int uart_d:1;              /* UART4  0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int uart_e:1;              /* UART5  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_1:1;               /* I2C1  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_2:1;               /* I2C2  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_3:1;               /* I2C3  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int dvc_i2c:1;             /* DVC-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int owr:1;                 /* OWR-I2C 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int i2c_4:1;               /* I2C4  0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int sl2b5:1;               /* SLINK 2B-5; 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int sl2b6:1;               /* SLINK 2B-6; 0 = NOT_ACTIVE 1 = ACTIVE */
        unsigned int undefined_bits_29_31:3;
    };

    uint32_t reg32;
} requestors_rx_t;

#define CNTRL_REG_OFFSET 0x10
#define CNTRL_REG_RESET  0x00000000
typedef union cntrl_reg_u {
    struct {
        unsigned int count_value:16;        /* DMA COUNT Value */
        unsigned int undefined_bits_16_31:16;
    };

    uint32_t reg32;
} cntrl_reg_t;

#define IRQ_STA_CPU_OFFSET 0x14
#define IRQ_STA_CPU_RESET  0x00000000
typedef union irq_sta_cpu_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel0 */
        unsigned int ch1:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel4; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel5; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel6; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel7; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel8; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Gathers all the after-masking CPU directed IRQ status bits from channel9; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel10; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel11; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel12; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel13; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel14; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel15; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel16; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel17; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel18; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel19; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel20; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel21; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel22; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel23; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel24; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel25; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel26; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel27; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel28; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel29; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel30; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31:1;                /* Gathers all the after-masking CPU directed IRQ status bits from channel31; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} irq_sta_cpu_t;

#define IRQ_STA_COP_OFFSET 0x18
#define IRQ_STA_COP_RESET  0x00000000
typedef union irq_sta_cop_u {
    struct {
        unsigned int ch0:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel0 */
        unsigned int ch1:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel2; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel3; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel4; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel5; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel6; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel7; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel8; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Gathers all the after-masking COP directed IRQ status bits from channel9; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel10; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel11; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel12; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel13; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel14; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel15; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel16; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel17; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel18; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel19; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel20; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel21; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel22; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel23; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel24; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel25; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel26; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel27; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel28; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel29; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel30; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31:1;                /* Gathers all the after-masking COP directed IRQ status bits from channel31; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} irq_sta_cop_t;

#define IRQ_MASK_OFFSET 0x1C
#define IRQ_MASK_RESET  0x00000000
typedef union irq_mask_u {
    struct {
        unsigned int ch0:1;                 /* Each bit allows the associated channel0 IRQ to propagate when '1' */
        unsigned int ch1:1;                 /* Each bit allows the associated channel1 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Each bit allows the associated channel2 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Each bit allows the associated channel3 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Each bit allows the associated channel4 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Each bit allows the associated channel5 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Each bit allows the associated channel6 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Each bit allows the associated channel7 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Each bit allows the associated channel8 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Each bit allows the associated channel9 IRQ to propagate when '1; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Each bit allows the associated channel10 IRQ to propagate when '1' 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Each bit allows the associated channel11 IRQ to propagate when '1' 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Each bit allows the associated channel12 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Each bit allows the associated channel13 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Each bit allows the associated channel14 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Each bit allows the associated channel15 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16:1;                /* Each bit allows the associated channel16 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17:1;                /* Each bit allows the associated channel17 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18:1;                /* Each bit allows the associated channel18 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19:1;                /* Each bit allows the associated channel19 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20:1;                /* Each bit allows the associated channel20 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21:1;                /* Each bit allows the associated channel21 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22:1;                /* Each bit allows the associated channel22 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23:1;                /* Each bit allows the associated channel23 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24:1;                /* Each bit allows the associated channel24 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25:1;                /* Each bit allows the associated channel25 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26:1;                /* Each bit allows the associated channel26 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27:1;                /* Each bit allows the associated channel27 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28:1;                /* Each bit allows the associated channel28 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29:1;                /* Each bit allows the associated channel29 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30:1;                /* Each bit allows the associated channel30 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31:1;                /* Each bit allows the associated channel31 IRQ to propagate when '1'; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} irq_mask_t;

#define IRQ_MASK_SET_OFFSET 0x20
#define IRQ_MASK_SET_RESET  0x00000000
typedef union irq_mask_set_u {
    struct {
        unsigned int ch0:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31:1;                /* Sets the Mask Register; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} irq_mask_set_t;

#define IRQ_MASK_CLR_OFFSET 0x24
#define IRQ_MASK_CLR_RESET  0x00000000
typedef union irq_mask_clr_u {
    struct {
        unsigned int ch0:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9:1;                 /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31:1;                /* Clears the Mask Register; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} irq_mask_clr_t;

#define TRIG_REG_OFFSET 0x28
#define TRIG_REG_RESET  0x00000000
typedef union trig_reg_u {
    struct {
        unsigned int undefined_bit_0:1;
        unsigned int smp_24:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_25:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_26:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int smp_27:1;              /* Semaphore requests SW initiated DMA request; 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int xrq_a:1;               /* XRQ.A (GPIOA) (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int xrq_b:1;               /* XRQ.B (GPIOB) (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int tmr1:1;                /* Trigger select from Timer (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int tmr2:1;                /* Trigger select from Timer (Hardware initiated DMA request); 0 = NOT_ACTIVE; 1 = ACTIVE */
        unsigned int undefined_bits_8_31:24;
    };

    uint32_t reg32;
} trig_reg_t;

#define CHANNEL_TRIG_REG_OFFSET 0x2C
#define CHANNEL_TRIG_REG_RESET  0x00000000
typedef union channel_trig_reg_u {
    struct {
        unsigned int apb_0:1;               /* EOC-0 Initiated DMA Request after transfer completion */
        unsigned int apb_1:1;               /* EOC-1 Initiated DMA Request after transfer completion */
        unsigned int apb_2:1;               /* EOC-2 Initiated DMA Request after transfer completion */
        unsigned int apb_3:1;               /* EOC-3 Initiated DMA Request after transfer completion */
        unsigned int apb_4:1;               /* EOC-4 Initiated DMA Request after transfer completion */
        unsigned int apb_5:1;               /* EOC-5 Initiated DMA Request after transfer completion */
        unsigned int apb_6:1;               /* EOC-6 Initiated DMA Request after transfer completion */
        unsigned int apb_7:1;               /* EOC-7 Initiated DMA Request after transfer completion */
        unsigned int apb_8:1;               /* EOC-8 Initiated DMA Request after transfer completion */
        unsigned int apb_9:1;               /* EOC-9 Initiated DMA Request after transfer completion */
        unsigned int apb_10:1;              /* EOC-10 Initiated DMA Request after transfer completion */
        unsigned int apb_11:1;              /* EOC-11 Initiated DMA Request after transfer completion */
        unsigned int apb_12:1;              /* EOC-12 Initiated DMA Request after transfer completion */
        unsigned int apb_13:1;              /* EOC-13 Initiated DMA Request after transfer completion */
        unsigned int apb_14:1;              /* EOC-14 Initiated DMA Request after transfer completion */
        unsigned int apb_15:1;              /* EOC-15 Initiated DMA Request after transfer completion */
        unsigned int apb_16:1;              /* EOC-16 Initiated DMA Request after transfer completion */
        unsigned int apb_17:1;              /* EOC-17 Initiated DMA Request after transfer completion */
        unsigned int apb_18:1;              /* EOC-18 Initiated DMA Request after transfer completion */
        unsigned int apb_19:1;              /* EOC-19 Initiated DMA Request after transfer completion */
        unsigned int apb_20:1;              /* EOC-20 Initiated DMA Request after transfer completion */
        unsigned int apb_21:1;              /* EOC-21 Initiated DMA Request after transfer completion */
        unsigned int apb_22:1;              /* EOC-22 Initiated DMA Request after transfer completion */
        unsigned int apb_23:1;              /* EOC-23 Initiated DMA Request after transfer completion */
        unsigned int apb_24:1;              /* EOC-24 Initiated DMA Request after transfer completion */
        unsigned int apb_25:1;              /* EOC-25 Initiated DMA Request after transfer completion */
        unsigned int apb_26:1;              /* EOC-26 Initiated DMA Request after transfer completion */
        unsigned int apb_27:1;              /* EOC-27 Initiated DMA Request after transfer completion */
        unsigned int apb_28:1;              /* EOC-28 Initiated DMA Request after transfer completion */
        unsigned int apb_29:1;              /* EOC-29 Initiated DMA Request after transfer completion */
        unsigned int apb_30:1;              /* EOC-30 Initiated DMA Request after transfer completion */
        unsigned int apb_31:1;              /* EOC-31 Initiated DMA Request after transfer completion */
    };

    uint32_t reg32;
} channel_trig_reg_t;

#define DMA_STATUS_OFFSET 0x30
#define DMA_STATUS_RESET  0x00000000
typedef union dma_status_u {
    struct {
        unsigned int ise_eoc_0:1;          /* DMA Channel0 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_1:1;          /* DMA Channel1 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_2:1;          /* DMA Channel2 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_3:1;          /* DMA Channel3 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_4:1;          /* DMA Channel4 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_5:1;          /* DMA Channel5 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_6:1;          /* DMA Channel6 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_7:1;          /* DMA Channel7 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_8:1;          /* DMA Channel8 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_9:1;          /* DMA Channel9 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_10:1;         /* DMA Channel10 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_11:1;         /* DMA Channel11 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_12:1;         /* DMA Channel12 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_13:1;         /* DMA Channel13 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_14:1;         /* DMA Channel14 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_15:1;         /* DMA Channel15 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_16:1;         /* DMA Channel16 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_17:1;         /* DMA Channel17 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_18:1;         /* DMA Channel18 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_19:1;         /* DMA Channel19 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_20:1;         /* DMA Channel20 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_21:1;         /* DMA Channel21 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_22:1;         /* DMA Channel22 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_23:1;         /* DMA Channel23 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_24:1;         /* DMA Channel24 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_25:1;         /* DMA Channel25 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_26:1;         /* DMA Channel26 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_27:1;         /* DMA Channel27 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_28:1;         /* DMA Channel28 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_29:1;         /* DMA Channel29 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_30:1;         /* DMA Channel30 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
        unsigned int ise_eoc_31:1;         /* DMA Channel31 Interrupt Status; 0 = NOT_ACTIVE, 1 = ACTIVE */
    };

    uint32_t reg32;
} dma_status_t;

#define CHANNEL_EN_REG_OFFSET 0x34
#define CHANNEL_EN_REG_RESET  0x00000000
typedef union channel_en_reg_u {
    struct {
        unsigned int ch0_cnt_en:1;          /* Enable the Channel0 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch1_cnt_en:1;          /* Enable the Channel1 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch2_cnt_en:1;          /* Enable the Channel2 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch3_cnt_en:1;          /* Enable the Channel3 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch4_cnt_en:1;          /* Enable the Channel4 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch5_cnt_en:1;          /* Enable the Channel5 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch6_cnt_en:1;          /* Enable the Channel6 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch7_cnt_en:1;          /* Enable the Channel7 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch8_cnt_en:1;          /* Enable the Channel8 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch9_cnt_en:1;          /* Enable the Channel9 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch10_cnt_en:1;         /* Enable the Channel10 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch11_cnt_en:1;         /* Enable the Channel11 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch12_cnt_en:1;         /* Enable the Channel12 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch13_cnt_en:1;         /* Enable the Channel13 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch14_cnt_en:1;         /* Enable the Channel14 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch15_cnt_en:1;         /* Enable the Channel15 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch16_cnt_en:1;         /* Enable the Channel16 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch17_cnt_en:1;         /* Enable the Channel17 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch18_cnt_en:1;         /* Enable the Channel18 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch19_cnt_en:1;         /* Enable the Channel19 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch20_cnt_en:1;         /* Enable the Channel20 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch21_cnt_en:1;         /* Enable the Channel21 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch22_cnt_en:1;         /* Enable the Channel22 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch23_cnt_en:1;         /* Enable the Channel23 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch24_cnt_en:1;         /* Enable the Channel24 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch25_cnt_en:1;         /* Enable the Channel25 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch26_cnt_en:1;         /* Enable the Channel26 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch27_cnt_en:1;         /* Enable the Channel27 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch28_cnt_en:1;         /* Enable the Channel28 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch29_cnt_en:1;         /* Enable the Channel29 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch30_cnt_en:1;         /* Enable the Channel30 count; 0 = DISABLE; 1 = ENABLE */
        unsigned int ch31_cnt_en:1;         /* Enable the Channel31 count; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} channel_en_reg_t;

#define CHANNEL_CSR_OFFSET 0x1000
#define CHANNEL_CSR_RESET  0x00000000
typedef union channel_csr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int wcount:14;             /* Number of 32bit word cycles */
        unsigned int req_sel:5;             /* 0 = CNTR_REQ; 1 = APBIF_CH0; 2 = APBIF_CH1; 3 = APBIF_CH2; 4 = APBIF_CH3; 5 = HSI; 6 = NA6; 7 = NA7; 8 = UART_A; 9 = UART_B; 10 = UART_C; 11 = DTV; 12 = NA12; 13 = NA13; 14 = NA14; 15 = SL2B1; 16 = SL2B2; 17 = SL2B3; 18 = SL2B4; 19 = UART_D; 20 = UART_E; 21 = I2C; 22 = I2C2; 23 = I2C3; 24 = DVC_I2C; 25 = OWR; 26 = I2C4; 27 = SL2B5; 28 = SL2B6; 29 = NA29; 30 = NA30; 31 = NA31 */
        unsigned int flow:1;                /* Flow Control Enable (Synchronize Burst Transfers) 1 = Link to DRQ source 0 = Independent of DRQ request; 0 = DISABLE; 1 = ENABLE */
        unsigned int trig_sel:5;            /* Enable on Non-Zero Value; 0 = NA1; 1 = SMP24; 2 = SMP25; 3 = SMP26; 4 = SMP27; 5 = XRQ_A; 6 = XRQ_B; 7 = TMR1; 8 = TMR2; 9 = APB_0; 10 = APB_1; 11 = APB_2; 12 = APB_3; 13 = APB_4; 14 = APB_5; 15 = APB_6; 16 = APB_7; 17 = APB_8; 18 = APB_9; 19 = APB_10; 20 = APB_11; 21 = APB_12; 22 = APB_13; 23 = APB_14; 24 = APB_15 */
        unsigned int once:1;                /* Run Once or Run Multiple Mode (Allow Retriggering of this Channel) 1 = Run for One Block Transfer 0 = Run for Multiple Block Transfer; 0 = MULTIPLE_BLOCK; 1 = SINGLE_BLOCK */
        unsigned int dir:1;                 /* DMA Transfer Direction 1 = AHB read to APB write 0 = APB read to AHB write; 0 = AHB_WRITE; 1 = AHB_READ */
        unsigned int hold:1;                /* Hold this Processor until DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int ie_eoc:1;              /* Interrupt when DMA Block Transfer Completes; 0 = DISABLE; 1 = ENABLE */
        unsigned int enb:1;                 /* Enable DMA channel transfer; 0 = DISABLE; 1 = ENABLE */
    };

    uint32_t reg32;
} channel_csr_t;

#define CHANNEL_STA_OFFSET 0x1004
#define CHANNEL_STA_RESET  0x00000000
#define CHANNEL_STA_WRMASK 0x4FFF0003
typedef union channel_sta_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int count:14;              /* Current 32bit word cycles Flags set /cleared by HW */
        unsigned int undefined_bits_16_27:12;
        unsigned int ping_pong_sts:1;       /* if dir = AHB_WRITE : 0 - ping buffer transfer completed ; 1 - pong buffer transfer completed if dir = AHB_READ : 1 - ping buffer transfer completed ; 0 - pong buffer transfer completed; 0 = PING_INTR_STS; 1 = PONG_INTR_STS */
        unsigned int halt:1;                /* Holding Status of Processor; 0 = NO_HALT; 1 = HALT */
        unsigned int ise_eoc:1;             /* Write '1' to clear the flag; 0 = NO_INTR; 1 = INTR */
        unsigned int bsy:1;                 /* indicates whether DMA Channel Status active or not; 0 = WAIT; 1 = ACTIVE */
    };

    uint32_t reg32;
} channel_sta_t;

#define CHANNEL_DMA_BYTE_STA_OFFSET 0x1008
#define CHANNEL_DMA_BYTE_STA_RESET  0x00000000
typedef union channel_dma_byte_sta_u {
    struct {
        unsigned int dma_count:26;          /* Indicates the actual DMA Data Transfer Count in bytes */
        unsigned int undefined_bits_26_31:6;
    };

    uint32_t reg32;
} channel_dma_byte_sta_t;

#define CHANNEL_AHB_PTR_OFFSET 0x1010
#define CHANNEL_AHB_PTR_RESET  0x00000000
typedef union channel_ahb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int ahb_base:30;           /* APB-DMA Starting Address for AHB Bus: SW writes to modify */
    };

    uint32_t reg32;
} channel_ahb_ptr_t;

#define CHANNEL_AHB_SEQ_OFFSET 0x1014
#define CHANNEL_AHB_SEQ_RESET  0x00002000
typedef union channel_ahb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int wrap:3;                /* AHB Address Wrap: AHB Address wrap-around window 0=No Wrap (default) 5=Wrap on 512 word window 1=Wrap on 32 word window 6=Wrap on 1024 word window 2=Wrap on 64 word window 7=Wrap on 2048 word window 3=Wrap on 128 word window 4=Wrap on 256 word window; 0 = NO_WRAP; 1 = WRAP_0N_32WORDS; 2 = WRAP_ON_64WORDS; 3 = WRAP_ON_128WORDS; 4 = WRAP_ON_256WORDS; 5 = WRAP_ON_512WORDS; 6 = WRAP_ON_1024WORDS; 7 = WRAP_ON_2048WORDS */
        unsigned int dbl_buf:1;             /* 2X Double Buffering Mode (For Run-Multiple Mode with No Wrap Operations) 1 = Reload Base Address for 2X blocks (reload every other time) 0 = Reload Base Address for 1X blocks (def) (reload each time) 0 = RELOAD_FOR_1X_BLOCKS 1 = RELOAD_FOR_2X_BLOCKS */
        unsigned int undefined_bits_20_23:4;
        unsigned int ahb_burst:3;           /* AHB Burst Size DMA Burst Length (encoded) 4 = 1 Word (1x32bits) 5 = 4 Words (4x32bits) else = 8 Words (8x32bits) default; 4 = DMA_BURST_1WORDS; 5 = DMA_BURST_4WORDS; 6 = DMA_BURST_8WORDS */
        unsigned int ahb_data_swap:1;       /* When enabled the data going to AHB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24] }; 0 = DISABLE; 1 = ENABLE */
        unsigned int ahb_bus_width:3;       /* AHB Bus Width 0 = 8 bit Bus (RSVD) 1 = 16 bit Bus (RSVD) 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit Bus (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int intr_enb:1;            /* 0 = send interrupt to COP */
    };

    uint32_t reg32;
} channel_ahb_seq_t;

#define CHANNEL_APB_PTR_OFFSET 0x1018
#define CHANNEL_APB_PTR_RESET  0x00000000
typedef union channel_apb_ptr_u {
    struct {
        unsigned int undefined_bits_0_1:2;
        unsigned int apb_base:18;           /* APB-DMA Starting address for APB Bus: APB Base address: Upper 12 bits are fixed at 0x700X:XXXX */
        unsigned int undefined_bits_20_31:12;
    };

    uint32_t reg32;
} channel_apb_ptr_t;

#define CHANNEL_APB_SEQ_OFFSET 0x101C
#define CHANNEL_APB_SEQ_RESET  0x00002001
typedef union channel_apb_seq_u {
    struct {
        unsigned int undefined_bits_0_15:16;
        unsigned int apb_addr_wrap:3;       /* APB Address Wrap-around Window 0 = No Wrap 1 = Wrap on 1 Word Window (def) 2 = Wrap on 2 Word Window 3 = Wrap on 4 Word Window 4 = Wrap on 8 Word Window 5 = Wrap on 16 Word Window 6 = Wrap on 32 Word Window 7 = Wrap on 64 Word Window (RSVD); 0 = NO_WRAP; 1 = WRAP_0N_1WORDS; 2 = WRAP_ON_2WORDS; 3 = WRAP_ON_4WORDS; 4 = WRAP_ON_8WORDS; 5 = WRAP_ON_16WORDS; 6 = WRAP_ON_32WORDS; 7 = WRAP_ON_64WORDS */
        unsigned int undefined_bits_19_26:8;
        unsigned int apb_data_swap:1;       /* When enabled the data going to APB gets swapped as [31:0] --> {[7:0], [15:8], [23:16], [31:24]}; 0 = DISBALE; 1 = ENABLE */
        unsigned int apb_bus_width:3;       /* 0 = 8 bit Bus 1 = 16 bit Bus 2 = 32 bit Bus (Def) 3 = 64 bit Bus (RSVD) 4 = 128 bit BUS (RSVD); 0 = BUS_WIDTH_8; 1 = BUS_WIDTH_16; 2 = BUS_WIDTH_32; 3 = BUS_WIDTH_64; 4 = BUS_WIDTH_128 */
        unsigned int undefined_bit_31:1;
    };

    uint32_t reg32;
} channel_apb_seq_t;

#endif // TEGRA_APB_DMA_H
