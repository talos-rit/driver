This Folder contains source code intended to be used on a microcontroller I2C peripheral device.
It's meant to emulate future components not yet in the possesion of the dev team.

At present (2025/03/25), it's meant to emulate the functionality of an ADC, and a GPIO extender with interrupt functionality.

It should respond to multiple addresses to properly immitate replacing multiple I2C peripheral devices.
This will require 2-5 addresses. One for the GPIO expander, 1-4 for the ADC (depending on model, we may need as many as 4 devices).

The microcontroller replacement (capable of handling 8 motors) will require:
  - I2C address masking
  - 9 digital GPIO
  - 16 analog inputs
  - I2C bus (not overlapping with the other GPIO)

Suggested board: Arduino Mega 2560

The microcontroller MVP (capable of handling 1 motor) will require:
  - At least 2 I2C addresses
  - 2 digital GPIO
  - 2 analog inputs
  - I2C bus (not overlapping with the other GPIO)

Suggested board: (Pretty much any recent Arduino/ESP32)

[Nano 33 IoT I2C resource](https://microchip.my.site.com/s/article/SAM-D-L-C-and-SAM-D5x-E5x---Multiple-Address-Match-in-I2C-Slave-mode)
