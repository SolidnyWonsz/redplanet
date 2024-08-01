set(KERNEL_SOURCES
	debug/assert.cpp
	init/main.cpp
	init/console.cpp
	init/boot.s
	init/gdt.cpp
	init/idt.cpp
	library/cstdlib.cpp
	library/cstring.cpp
	library/cxxabi.cpp
	memory/vmm.cpp
	memory/heap.cpp
	tasking/scheduler.cpp
	tasking/process.cpp
	timer/timer.cpp
)

add_link_options(-T${PROJECT_SOURCE_DIR}/kernel/init/linker.ld)
add_link_options(-ffreestanding)
add_link_options(-O2)
add_link_options(-nostdlib)
add_link_options(-lgcc)

include_directories(.)

add_executable(redplanet ${KERNEL_SOURCES})

target_compile_options(redplanet
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti>
)