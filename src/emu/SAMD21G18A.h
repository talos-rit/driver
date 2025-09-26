#pragma once

// Chip used by the Arduino Nano 33 IoT

#include <stdint.h>

#pragma pack(push, 1)
typedef struct _samd21g18a_sercom
{
    #define SAMD21G18A_SERCOMn_BASE_ADDR(n) (0x42000800 + n * 0x400)
    volatile uint32_t   CTRLA;      // 0x00
        #define SAMD21G18A_SERCOM_CTRLA_SWRST                   _BITULL(0)
        #define SAMD21G18A_SERCOM_CTRLA_ENABLE                  _BITULL(1)
        #define SAMD21G18A_SERCOM_CTRLA_MODE_MASK               (0x001C)
        #define SAMD21G18A_SERCOM_CTRLA_MODE_OFFSET             (2)
        #define SAMD21G18A_SERCOM_CTRLA_MODE_USART_EXTCLK       0X00
        #define SAMD21G18A_SERCOM_CTRLA_MODE_USART_INTCLK       0X01
        #define SAMD21G18A_SERCOM_CTRLA_MODE_SPI_SLAVE          0X02
        #define SAMD21G18A_SERCOM_CTRLA_MODE_SPI_MASTER         0X03
        #define SAMD21G18A_SERCOM_CTRLA_MODE_I2C_SLAVE          0X04
        #define SAMD21G18A_SERCOM_CTRLA_MODE_I2C_MASTER         0X05
        #define SAMD21G18A_SERCOM_CTRLA_RUNSTDBY                _BITULL(7)
        #define SAMD21G18A_SERCOM_CTRLA_IBON                    _BITULL(8)
        #define SAMD21G18A_SERCOM_CTRLA_DOPO_MASK               0x00030000
        #define SAMD21G18A_SERCOM_CTRLA_DOPO_OFFSET             (16)
        #define SAMD21G18A_SERCOM_CTRLA_DIPO_MASK               0x00300000
        #define SAMD21G18A_SERCOM_CTRLA_DIPO_OFFSET             (20)
        #define SAMD21G18A_SERCOM_CTRLA_DIPO_SERCOM_PADn(n)     (n)
        #define SAMD21G18A_SERCOM_CTRLA_FORM_MASK               0x0F000000
        #define SAMD21G18A_SERCOM_CTRLA_FORM_OFFSET             (24)
        #define SAMD21G18A_SERCOM_CTRLA_FORM_SPI                0x00
        #define SAMD21G18A_SERCOM_CTRLA_FORM_SPI_ADDR           0x02
        #define SAMD21G18A_SERCOM_CTRLA_CPHA                    _BITULL(28)
        #define SAMD21G18A_SERCOM_CTRLA_CPOL                    _BITULL(29)
        #define SAMD21G18A_SERCOM_CTRLA_DORD                    _BITULL(30)
    volatile uint32_t   CTRLB;      // 0x04
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_MASK            0x00C00000
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_OFFSET          (22)
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_NONE            0X00
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_TXFIFO          0X01
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_RXFIFO          0X02
        #define SAMD21G18A_SERCOM_CTRLB_FIFOCLR_BOTH            0X03
        #define SAMD21G18A_SERCOM_CTRLB_RXEN                    _BITULL(17)
        #define SAMD21G18A_SERCOM_CTRLB_AMODE_MASK              0x0000C000
        #define SAMD21G18A_SERCOM_CTRLB_AMODE_OFFSET            (14)
        #define SAMD21G18A_SERCOM_CTRLB_MSSEN                   _BITULL(13)
        #define SAMD21G18A_SERCOM_CTRLB_SSDE                    _BITULL(9)
        #define SAMD21G18A_SERCOM_CTRLB_PLOADEN                 _BITULL(6)
        #define SAMD21G18A_SERCOM_CTRLB_CHSIZE                  _BITULL(0)
    volatile uint32_t   RESERVED0;  // 0x08
    volatile uint32_t   BAUD;       // 0x0C
    volatile uint32_t   RESERVED1;  // 0x10
    volatile uint8_t    INTENCLR;   // 0x14
    volatile uint8_t    RESERVED2;  // 0x15
    volatile uint8_t    INTFLAG;    // 0x16
    volatile uint8_t    RESERVED2;  // 0x17
    volatile uint8_t    INTFLAG;    // 0x18
    volatile uint8_t    RESERVED2;  // 0x19
    volatile uint16_t   STATUS;     // 0x1A
    volatile uint32_t   SYNCBUSY;   // 0x1C
        #define SAMD21G18A_SERCOM_SYNCBUSY_CTRLB                _BITULL(2)
        #define SAMD21G18A_SERCOM_SYNCBUSY_ENABLE               _BITULL(1)
        #define SAMD21G18A_SERCOM_SYNCBUSY_SWRST                _BITULL(0)
    volatile uint32_t   RESERVED3;  // 0x20
    volatile uint32_t   ADDR;       // 0x24
    volatile uint16_t   DATA;       // 0x28
    volatile uint32_t   RESERVED4;  // 0x2A
    volatile uint16_t   RESERVED4;  // 0x2E
    volatile uint8_t    DBGCTRL;    // 0x30
    volatile uint8_t    RESERVED5;  // 0x31
    volatile uint16_t   RESERVED5;  // 0x32
    volatile uint16_t   FIFOSPACE;  // 0x34
    volatile uint16_t   FIFOSPACE;  // 0x36
} SAMD21G18A_SERCOM;
#pragma pack(pop)