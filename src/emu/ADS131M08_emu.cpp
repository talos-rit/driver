#include <endian.h>
#include <string.h>

#include "adc/ADS131M08.h"
#include "emu/ADS131M08_emu.h"

#define ADS131M08_CMD  ADS131M08::ADS131M08_Command  // This is getting annoying
#define ADS131M08_RESP ADS131M08::ADS131M08_Response // This is getting annoying

static bool valid_reg_op(uint8_t addr, uint8_t reg_len)
{
    return (addr + reg_len > 0x3F + 1) ? false : true;
}

void ADS131M08_Emulator::ExecuteCommand(ADS131M08::ADS131M08_Command cmd, const uint8_t* src, uint16_t data_len,
                    uint8_t* resp, uint16_t* resp_len)
{

    uint8_t reg_addr = 0;
    uint8_t reg_len  = 0;
    uint16_t cmd_int = (uint16_t) cmd;
    if (cmd & ADS131M08_CMD::ADS131M08_CMD_WREG_CMD ||
        cmd & ADS131M08_CMD::ADS131M08_CMD_RREG_CMD)
    {
        reg_addr = (0x1F80 & cmd) >> 7;
        reg_len  = 0x007F & cmd;
        cmd_int &= 0xE000;
        if (!valid_reg_op(reg_addr, reg_len)) ExecuteCommand(ADS131M08_CMD::ADS131M08_CMD_NULL_CMD, src, data_len, resp, resp_len);
    }

    switch (cmd_int)
    {
        case ADS131M08_CMD::ADS131M08_CMD_NULL_CMD:
            // Intentional fallthrough
        default:
            uint8_t* dst = resp;

            *((uint16_t*)dst) = htobe16(ads_regs.STATUS);
            *resp_len = sizeof(uint16_t);

            for (uint8_t ch_iter = 0; ch_iter < 8; ch_iter++)
            {
                *((uint32_t*)(dst + *resp_len)) = htobe32(ads_channels[ch_iter]);
                *resp_len += sizeof(uint32_t);
            }

            break;
        case ADS131M08_CMD::ADS131M08_CMD_RESET_CMD:
            Reset();
            *((uint16_t*)resp) = htobe16(ADS131M08_RESP::ADS131M08_RESP_RESET);
            *resp_len = sizeof(uint16_t);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_STANDBY_CMD:
            Standby();
            *((uint16_t*)resp) = htobe16(ADS131M08_RESP::ADS131M08_RESP_STANDBY);
            *resp_len = sizeof(uint16_t);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_WAKEUP_CMD:
            Wakeup();
            *((uint16_t*)resp) = htobe16(ADS131M08_RESP::ADS131M08_RESP_WAKEUP);
            *resp_len = sizeof(uint16_t);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_LOCK_CMD:
            Lock();
            *((uint16_t*)resp) = htobe16(ADS131M08_RESP::ADS131M08_RESP_LOCK);
            *resp_len = sizeof(uint16_t);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_UNLOCK_CMD:
            Unlock();
            *((uint16_t*)resp) = htobe16(ADS131M08_RESP::ADS131M08_RESP_UNLOCK);
            *resp_len = sizeof(uint16_t);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_RREG_CMD:
            uint8_t* dst = resp;
            *resp_len = sizeof(uint16_t);

            if (reg_len > 1)
            {
                *((uint16_t*)dst) = htobe16(ADS131M08_RESP::ADS131M08_RESP_RREG | (cmd & ~0xE000));
                dst += sizeof(uint16_t);
                *resp_len += reg_len * sizeof(uint16_t);
            }

            ReadReg(dst, reg_addr, reg_len);
            break;
        case ADS131M08_CMD::ADS131M08_CMD_WREG_CMD:
            uint8_t* dst = resp;
            *resp_len = sizeof(uint16_t);

            if (reg_len > 1)
            {
                *((uint16_t*)dst) = htobe16(ADS131M08_RESP::ADS131M08_RESP_RREG | (cmd & ~0xE000));
                dst += sizeof(uint16_t);
                *resp_len += reg_len * sizeof(uint16_t);
            }
            WriteReg(src, reg_addr, reg_len);
            break;
    }
}

void ADS131M08_Emulator::Null()
{

}

void ADS131M08_Emulator::Reset()
{
    ADS131M08::ResetRegs(&ads_regs);
    SyncRegisters();
}

void ADS131M08_Emulator::Standby()
{

}

void ADS131M08_Emulator::Wakeup()
{

}

void ADS131M08_Emulator::Lock()
{

}

void ADS131M08_Emulator::Unlock()
{

}

#if 0
static int sizeof_reg_addr(uint8_t addr)
{
    if (addr > 0x3F) return -1;
    int size = sizeof(uint16_t);

    if (addr >= ADS131M08_REG_CH_CFG_ADDR(0) &&
        addr <  ADS131M08_REG_CH_CFG_ADDR(8) &&
        0x00 != (addr - ADS131M08_REG_CH_CFG_ADDR(0)) % ADS131M08_CHANNEL_CONFIG_LEN)
    {
        size = sizeof(uint32_t);
    }

    if (0x07 == addr)
    {
        size = sizeof(uint32_t);
    }

    return size;
}
#endif

static void split_32_to_be16(uint16_t* dst, uint32_t src)
{
    dst[0] = htobe16((0xFFFF0000 & src) >> 16);
    dst[1] = htobe16((0x0000FFFF & src));
}

void ADS131M08_Emulator::SyncRegisters()
{
    ADS131M08_Regs* src_regs = &ads_regs;
    ADS131M08_Regs* dst_regs = &native_regs;

    memcpy(dst_regs, src_regs, sizeof(ADS131M08::ADS131M08_Regs));

    // Fix threshold
    split_32_to_be16(((uint16_t*) dst_regs) + ADS131M08_REG_THRSHLD_ADDR, src_regs->THRSHLD);

    // Fix Channel configs
    for(uint8_t ch_iter = 0; ch_iter < 8; ch_iter++)
    {
        split_32_to_be16(   ((uint16_t*) dst_regs) + ADS131M08_REG_CH_CFG_ADDR(ch_iter) + ADS131M08_CHANNEL_CONFIG_OCAL_OFFSET,
                            src_regs->ch_cfgs[ch_iter].OCAL);
        split_32_to_be16(   ((uint16_t*) dst_regs) + ADS131M08_REG_CH_CFG_ADDR(ch_iter) + ADS131M08_CHANNEL_CONFIG_GCAL_OFFSET,
                            src_regs->ch_cfgs[ch_iter].GCAL);
    }
}

int ADS131M08_Emulator::ReadReg(uint8_t* dst, uint8_t addr, uint8_t reg_len)
{
    if (!valid_reg_op(addr, reg_len)) return -1;

    uint16_t* src_16    = ((uint16_t*) &ads_regs);
    uint16_t* dst_16    = ((uint16_t*) dst);
    memcpy(&dst_16[0], &src_16[addr], reg_len * sizeof(uint16_t));

    return reg_len;
}

int ADS131M08_Emulator::WriteReg(const uint8_t* src, uint8_t addr, uint8_t reg_len)
{
    if (!valid_reg_op(addr, reg_len)) return -1;

    uint16_t* src_16    = ((uint16_t*) src);
    uint16_t* dst_16    = ((uint16_t*) &ads_regs);
    memcpy(&dst_16[0], &src_16[addr], reg_len * sizeof(uint16_t));

    SyncRegisters();
    return reg_len;
}


void ADS131M08_Emulator::ReadChannels()
{
    // TODO: Implement

    // Dummy:
    for (uint8_t ch_iter = 0; ch_iter < 8; ch_iter++)
    {
        uint8_t fill = ch_iter | ch_iter << 4;
        memset(&ads_channels[ch_iter], fill, sizeof(ads_channels[0]));
    }
}