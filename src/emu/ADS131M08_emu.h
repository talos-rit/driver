#pragma once

#include "adc/ADS131M08.h"

class ADS131M08_Emulator : public ADS131M08
{
private:
    ADS131M08_Regs native_regs;
    ADS131M08_Regs ads_regs;
    uint32_t native_channels[8];    // Channels formatted for native operations (converted channels)

    void ADS131M08_Emulator::SyncRegisters();
public:
    void ReadChannels();

    /**
     * @brief Interfaces with the ADS's SPI port
     * @details Overwrites the data and data_len values with the response
     * @param cmd The command to be executed
     * @param data The data related to the command (may be NULL if data_len is 0 (no payload))
     * @param data_len The length of the payload in bytes
     * @returns -1 on failure, length of response in bytes on success
     */
    void ExecuteCommand(ADS131M08_Command cmd, const uint8_t* src, uint16_t data_len,
                        uint8_t* resp, uint16_t* resp_len);

    void Null();
    void Reset();
    void Standby();
    void Wakeup();
    void Lock();
    void Unlock();
    int ReadReg(uint8_t* dst, uint8_t addr, uint8_t reg_len);
    int WriteReg(const uint8_t* src, uint8_t addr, uint8_t reg_len);
};