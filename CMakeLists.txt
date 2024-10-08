cmake_minimum_required(VERSION 3.21)

project(redplanet CXX ASM)

set(CMAKE_SYSTEM_NAME "Red Planet")
set(CMAKE_CXX_COMPILER i686-elf-gcc)
set(CMAKE_ASM_COMPILER i686-elf-as)

add_subdirectory(kernel)

set(QEMU_OPTIONS -m 64M)

# TO DO:
# Make better "qemu-run" target that actually knows where Red Planet's binary is located.

add_custom_target(qemu-run
    COMMAND qemu-system-i386 -kernel ${CMAKE_BINARY_DIR}/kernel/redplanet ${QEMU_OPTIONS}
    DEPENDS redplanet
    USES_TERMINAL
)

add_custom_target(qemu-gdb-run
    COMMAND qemu-system-i386 -s -S -kernel ${CMAKE_BINARY_DIR}/kernel/redplanet ${QEMU_OPTIONS}
    DEPENDS redplanet
    USES_TERMINAL
)

add_custom_target(grub-iso
    COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/iso/boot/grub
    COMMAND cp ${PROJECT_SOURCE_DIR}/meta/grub.cfg ${PROJECT_SOURCE_DIR}/iso/boot/grub
    COMMAND cp ${CMAKE_BINARY_DIR}/kernel/redplanet ${PROJECT_SOURCE_DIR}/iso/boot
    COMMAND grub-mkrescue iso -o ${PROJECT_BINARY_DIR}/redplanet.iso
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS redplanet
    USES_TERMINAL
)

add_custom_target(grub2-iso
    COMMAND mkdir -p ${PROJECT_SOURCE_DIR}/iso/boot/grub
    COMMAND cp ${PROJECT_SOURCE_DIR}/meta/grub.cfg ${PROJECT_SOURCE_DIR}/iso/boot/grub
    COMMAND cp ${CMAKE_BINARY_DIR}/kernel/redplanet ${PROJECT_SOURCE_DIR}/iso/boot
    COMMAND grub2-mkrescue iso -o ${PROJECT_BINARY_DIR}/redplanet.iso
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    DEPENDS redplanet
    USES_TERMINAL
)