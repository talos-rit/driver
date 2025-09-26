#include <stdlib.h>
#include <string.h>

#include "adc/ADS131M08.h"

#include "util/comm.h"
#include "crc/crc.h"
#include "crc/ansi.h"
#include "crc/ccitt.h"


ADS131M08::ADS131M08()
{
    memset(&ads_channels[0], 0, 8 * sizeof(uint32_t));
    crc_table = crc16_table_ccitt;
    seed = 0xFFFF;
}

ADS131M08::~ADS131M08() {}

void ADS131M08::ResetChannelConfig(ADS131M08_CHANNEL_CONFIG* ch_cfg)
{
    ch_cfg->CFG         = ADS131M08_CHANNEL_CONFIG_CFG_RESET_VALUE;
    ch_cfg->OCAL        = ADS131M08_CHANNEL_CONFIG_OCAL_RESET_VALUE;
    ch_cfg->GCAL        = ADS131M08_CHANNEL_CONFIG_GCAL_RESET_VALUE;
}

void ADS131M08::ResetRegs(ADS131M08_Regs* regs)
{
    memset(regs, 0, sizeof(ADS131M08_Regs));

    regs->ID            = ADS131M08_REG_ID_RESET_VALUE;
    regs->STATUS        = ADS131M08_REG_CFG_RESET_VALUE;
    regs->MODE          = ADS131M08_REG_MODE_RESET_VALUE;
    regs->CLOCK         = ADS131M08_REG_CLOCK_RESET_VALUE;
    regs->GAIN1         = ADS131M08_REG_GAIN_RESET_VALUE;
    regs->GAIN2         = ADS131M08_REG_GAIN_RESET_VALUE;
    regs->CFG           = ADS131M08_REG_CFG_RESET_VALUE;
    regs->THRSHLD       = ADS131M08_REG_THRSHLD_RESET_VALUE;
    regs->REGMAP_CRC    = ADS131M08_REG_REGMAP_CRC_RESET_VALUE;
    regs->RESERVED      = ADS131M08_REG_RESERVED_RESET_VALUE;

    for (uint8_t ch_iter = 0; ch_iter < 8; ch_iter++)
    {
        ResetChannelConfig(&regs->ch_cfgs[ch_iter]);
    }
}