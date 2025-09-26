#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <linux/const.h>

#include "emu/ADS131M08_emu.h"
#include "emu/SAMD21G18A.h"


ADS131M08_Emulator ads;
SAMD21G18A_SERCOM* spi;

void spi_setup()
{
    // Init SPI on SERCOM1
    spi = (SAMD21G18A_SERCOM*) SAMD21G18A_SERCOMn_BASE_ADDR(1);
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_SWRST;
    while(spi->SYNCBUSY & SAMD21G18A_SERCOM_SYNCBUSY_SWRST) usleep(1000);

    // Set SPI mode
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_MODE_SPI_SLAVE << SAMD21G18A_SERCOM_CTRLA_MODE_OFFSET;
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_CPHA;                                                            // CPHA = 1; (CPOL = 0 at reset)
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_FORM_SPI << SAMD21G18A_SERCOM_CTRLA_FORM_OFFSET;

    // MOSI/MISO setup (default pins)
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_DIPO_SERCOM_PADn(3) << SAMD21G18A_SERCOM_CTRLA_DIPO_OFFSET;
    spi->CTRLA |= 0x0 << SAMD21G18A_SERCOM_CTRLA_DOPO_OFFSET;

    spi->CTRLB |= SAMD21G18A_SERCOM_CTRLB_CHSIZE;

    // DORD set by default to MSB

    // Setup DMA

    // Start DMA
    // Start SPI
    spi->CTRLA |= SAMD21G18A_SERCOM_CTRLA_ENABLE;
}

void setup()
{
    spi_setup();
    ads.Reset();
}

void loop()
{
    ads.ReadChannels();
}