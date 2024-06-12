cmake_minimum_required(VERSION 3.21)

project(redplanet CXX ASM)

set(CMAKE_SYSTEM_NAME "Red Planet")
set(CMAKE_CXX_COMPILER i686-elf-gcc)
set(CMAKE_ASM_COMPILER i686-elf-as)

add_subdirectory(kernel)

# TO DO:
# Make better "qemu-run" target that actually knows where Red Planet's binary is located.

add_custom_target(qemu-run
    COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/kernel/redplanet -m 64M
    DEPENDS redplanet
    USES_TERMINAL
)