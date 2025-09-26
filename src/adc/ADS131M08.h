#pragma once

#include <stdint.h>

class ADS131M08
{
public:
    #pragma pack(push, 1)

    // Note: always write 0s to reserved fields
    // _BITULL is used for bitflipping boolean registers
    // Multi-bit values are saved as the offset within the register

    typedef struct ads131m08_ch_cfg
    {
        #define ADS131M08_CHANNEL_CONFIG_LEN                    (0x03)
        uint16_t CFG;
            #define ADS131M08_CHANNEL_CONFIG_CFG_OFFSET         0x00
            #define ADS131M08_CHANNEL_CONFIG_CFG_PHASE          (8)
            #define ADS131M08_CHANNEL_CONFIG_CFG_DCBLK_DIS      _BITULL(2)
            #define ADS131M08_CHANNEL_CONFIG_CFG_MUX            (0)
            #define ADS131M08_CHANNEL_CONFIG_CFG_UNDEF_MASK     0x0038
            #define ADS131M08_CHANNEL_CONFIG_CFG_RESET_VALUE    0x0000
        uint32_t OCAL;
            #define ADS131M08_CHANNEL_CONFIG_OCAL_OFFSET        0x01
            #define ADS131M08_CHANNEL_CONFIG_OCAL_VALUE         (8)
            #define ADS131M08_CHANNEL_CONFIG_OCAL_UNDEF_MASK    0x0000000F
            #define ADS131M08_CHANNEL_CONFIG_OCAL_RESET_VALUE   0x00000000
        uint32_t GCAL;
            #define ADS131M08_CHANNEL_CONFIG_GCAL_OFFSET        0x02
            #define ADS131M08_CHANNEL_CONFIG_GCAL_VALUE         (8)
            #define ADS131M08_CHANNEL_CONFIG_GCAL_UNDEF_MASK    0x0000000F
            #define ADS131M08_CHANNEL_CONFIG_GCAL_RESET_VALUE   0x80000000
    } ADS131M08_CHANNEL_CONFIG;

    typedef struct ads131m08_registers
    {
        uint16_t ID;
            #define ADS131M08_REG_ID_ADDR                       0x00
            #define ADS131M08_REG_ID_RESET_VALUE                0x2800      // LSB undefined; can be any value
        uint16_t STATUS;    // Read only
            #define ADS131M08_REG_STATUS_ADDR                   0x01
            #define ADS131M08_REG_STATUS_LOCK                   _BITULL(15)
            #define ADS131M08_REG_STATUS_F_RESYNC               _BITULL(14)
            #define ADS131M08_REG_STATUS_REG_MAP                _BITULL(13)
            #define ADS131M08_REG_STATUS_CRC_ERR                _BITULL(12)
            #define ADS131M08_REG_STATUS_CRC_TYPE               _BITULL(11)
            #define ADS131M08_REG_STATUS_RESET                  _BITULL(10)
            #define ADS131M08_REG_STATUS_WLENGTH                (8)         // bits 9:8
            #define ADS131M08_REG_STATUS_DRDY(n)                _BITULL(n)
            #define ADS131M08_REG_STATUS_RESET_VALUE            0x0500
        uint16_t MODE;      // R/W
            // bits 15:14 reserved
            #define ADS131M08_REG_MODE_ADDR                     0x02
            #define ADS131M08_REG_MODE_REG_CRC_EN               _BITULL(13)
            #define ADS131M08_REG_MODE_RX_CRC_EN                _BITULL(12)
            #define ADS131M08_REG_MODE_CRC_TYPE                 _BITULL(11)
            #define ADS131M08_REG_MODE_RESET                    _BITULL(10)
            #define ADS131M08_REG_MODE_WLENGTH                  (8)         // bits 9:8
            // bits 7:5 reserved
            #define ADS131M08_REG_MODE_TIMEOUT                  _BITULL(4)
            #define ADS131M08_REG_MODE_DRDY_SEL                 (2)         // bits 3:2
            #define ADS131M08_REG_MODE_DRDY_HiZ                 _BITULL(1)
            #define ADS131M08_REG_MODE_DRDY_FMT                 _BITULL(0)
            // reserved mask
            #define ADS131M08_REG_MODE_UNDEF_MASK               0xC0E0      // bits 15:14 | 7:5
            #define ADS131M08_REG_MODE_RESET_VALUE              0x0510
        uint16_t CLOCK;
            #define ADS131M08_REG_CLOCK_ADDR                    0x03
            #define ADS131M08_REG_CLOCK_CHn_EN(n)               _BITULL(n+8)
            #define ADS131M08_REG_CLOCK_XTAL_DIS                _BITULL(7)
            #define ADS131M08_REG_CLOCK_EXTREF_EN               _BITULL(6)
            #define ADS131M08_REG_CLOCK_OSR                     (2)         // bits 4:2
            #define ADS131M08_REG_CLOCK_PWR                     (0)         // bits 1:0
            #define ADS131M08_REG_CLOCK_UNDEF_MASK              _BITULL(5)
            #define ADS131M08_REG_CLOCK_RESET_VALUE             0xFF0E
        uint16_t GAIN1;
            #define ADS131M08_REG_GAIN1_ADDR                    0x04
            // The following work for both GAIN1 and GAIN2
            #define ADS131M08_REG_GAIN_PGAGAINn(n)              ((n & ~_BITULL(2)) << 2)  // only difference between GAIN1 and GAIN2 is second bit: clear it
            #define ADS131M08_REG_GAIN_UNDEF_MASK               0x8888      // MSB of every nibble
            #define ADS131M08_REG_GAIN_RESET_VALUE              0x0000      // MSB of every nibble
        uint16_t GAIN2;
            #define ADS131M08_REG_GAIN2_ADDR                    0x05
        uint16_t CFG;
            #define ADS131M08_REG_CFG_ADDR                      0x06
            #define ADS131M08_REG_CFG_GC_DLY                    (9)
            #define ADS131M08_REG_CFG_GC_EN                     _BITULL(8)
            #define ADS131M08_REG_CFG_CD_ALLCH                  _BITULL(7)
            #define ADS131M08_REG_CFG_CD_NUM                    (4)
            #define ADS131M08_REG_CFG_CD_LEN                    (1)
            #define ADS131M08_REG_CFG_CD_EN                     _BITULL(0)
            #define ADS131M08_REG_CFG_UNDEF_MASK                0xE000
            #define ADS131M08_REG_CFG_RESET_VALUE               0x0600      // MSB of every nibble
        uint32_t THRSHLD;
            #define ADS131M08_REG_THRSHLD_ADDR                  0x07
            #define ADS131M08_REG_THRSHLD_CD_TH                 (8)
            #define ADS131M08_REG_THRSHLD_DCBLOCK               (0)
            #define ADS131M08_REG_THRSHLD_UNDEF_MASK            _BITULL(5)
            #define ADS131M08_REG_THRSHLD_RESET_VALUE           0x00000000
        ADS131M08_CHANNEL_CONFIG ch_cfgs[8];
            #define ADS131M08_REG_CH_CFG_ADDR(n)                (0x09 + n * ADS131M08_CHANNEL_CONFIG_LEN)
        uint16_t REGMAP_CRC;
            #define ADS131M08_REG_REGMAP_CRC_RESET_VALUE        0x00000000
        uint16_t RESERVED;
            #define ADS131M08_REG_RESERVED_RESET_VALUE          0x00000000
    } ADS131M08_Regs;

    typedef enum ads131m08_wlength
    {
        ADS131M08_WLEN_16b                                      = 0b00,
        ADS131M08_WLEN_24b                                      = 0b01, // default
        ADS131M08_WLEN_32b_zero_pad                             = 0b10, // last 8 bits are zeros
        ADS131M08_WLEN_32b_sign_ext_24b                         = 0b11, // first 8 bits are sign extension (0s if positive, Fs if negative?)
    } ADS131M08_WLENGTH;

    typedef enum ads131m08_cmd
    {
        // Any invalid command will be t                        reated as null
        ADS131M08_CMD_NULL_CMD                                  = 0x0000,   // Performs no actions; used for reading out channel data;
        ADS131M08_CMD_RESET_CMD                                 = 0x0011,
        ADS131M08_CMD_STANDBY_CMD                               = 0x0022,
        ADS131M08_CMD_WAKEUP_CMD                                = 0x0033,
        ADS131M08_CMD_LOCK_CMD                                  = 0x0555,
        ADS131M08_CMD_UNLOCK_CMD                                = 0x0655,
        ADS131M08_CMD_RREG_CMD                                  = 0xA000,
        ADS131M08_CMD_WREG_CMD                                  = 0x6000,
    } ADS131M08_Command;

    typedef enum ads131m08_resp
    {
        // The response of RESP_NULL will vary with the state of the ADS131M08 (STATUS register)
        ADS131M08_RESP_RESET                                    = 0xFF28,
        ADS131M08_RESP_STANDBY                                  = 0x0022,
        ADS131M08_RESP_WAKEUP                                   = 0x0033,
        ADS131M08_RESP_LOCK                                     = 0x0555,
        ADS131M08_RESP_UNLOCK                                   = 0x0655,
        ADS131M08_RESP_RREG                                     = 0xE000,   // The response of RESP_RREG will vary with the state of the ADS131M08 (Contents/Address of the requested registers)
        ADS131M08_RESP_WREG                                     = 0x4000,   // The response of RESP_WREG will vary with the state of the ADS131M08 (Contents/Address of the requested registers)
    } ADS131M08_Response;

    #pragma pack(pop)

protected:
    uint32_t ads_channels[8];       // Channels properly formatted to the ADS131M08
    const uint16_t *crc_table;
    uint16_t seed;

    static void ResetChannelConfig(ADS131M08_CHANNEL_CONFIG* ch_cfg);
    static void ResetRegs(ADS131M08_Regs* regs);
    static void ProcessRegs(ADS131M08_Regs* regs);


public:
    ADS131M08();
    ~ADS131M08();

    /**
     * @brief Interfaces with the ADS's SPI port
     * @details Overwrites the data and data_len values with the response
     * @param cmd The command to be executed
     * @param data The data related to the command (may be NULL if data_len is 0 (no payload))
     * @param data_len The length of the payload in bytes
     * @returns -1 on failure, length of response in bytes on success
     */
    virtual void ExecuteCommand(ADS131M08_Command cmd, const uint8_t* src, uint16_t data_len,
                        uint8_t* resp, uint16_t* resp_len);

    virtual void Null();
    virtual void Reset();
    virtual void Standby();
    virtual void Wakeup();
    virtual void Lock();
    virtual void Unlock();
    virtual int ReadReg(uint8_t* dst, uint8_t addr, uint8_t reg_len);
    virtual int WriteReg(const uint8_t* src, uint8_t addr, uint8_t reg_len);
};
