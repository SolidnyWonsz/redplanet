set(ARCH_SRC
	arch/cpu/exceptions.cpp
	arch/cpu/gdt.cpp
	arch/cpu/idt.cpp
	arch/cpu/isr.s
	arch/cpu/pic.cpp
	arch/init/boot.s
	arch/init/console.cpp
	arch/init/main.cpp
)

set(DEBUG_SRC
	debug/assert.cpp
)

set(LIBRARIES
	library/cstdlib.cpp
	library/cstring.cpp
	library/cxxabi.cpp
)

set(TIMER_SRC
	timer/timer.cpp
)

set(MEM_SRC
	memory/heap.cpp
	memory/vmm.cpp
)

set(TASK_SRC
	tasking/process.cpp
	tasking/scheduler.cpp
)

set(KERNEL_SRC ${ARCH_SRC} ${DEBUG_SRC} ${LIBRARIES} ${TIMER_SRC} ${MEM_SRC} ${TASK_SRC})
set(LINKER_LOCATION ${PROJECT_SOURCE_DIR}/kernel/arch/init/linker.ld)

add_link_options(-T${LINKER_LOCATION})
add_link_options(-ffreestanding)
add_link_options(-O2)
add_link_options(-nostdlib)
add_link_options(-lgcc)

include_directories(.)

add_executable(redplanet ${KERNEL_SRC})

target_compile_options(redplanet
	PRIVATE $<$<COMPILE_LANGUAGE:CXX>:-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti>
)