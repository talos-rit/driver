#pragma once

typedef enum _mcu_return_code
{
    OK              = 0,
    ERR             = -1,
    NOT_IMPLEMENTED = 2,
    NOT_SUPPORTED   = 3,
} MCU_Return;