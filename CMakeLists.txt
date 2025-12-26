# Driver library (subdirectory of Ichor)
add_library(driver STATIC)

# C++ sources
target_sources(driver PRIVATE
    src/serial/serial.cpp
    src/serial/i2c_dev.cpp
    src/dac/PCA9685PW.cpp
    src/gpio/isr.cpp
    src/enc/encoder.cpp
    src/motor/motor.cpp
    src/driver/driver.cpp
)

# Include directories
target_include_directories(driver PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(driver PUBLIC
    common
    Threads::Threads
)

# Set position independent code
set_target_properties(driver PROPERTIES
    POSITION_INDEPENDENT_CODE ON
)
