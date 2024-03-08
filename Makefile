#Architecture defaults to x86_64
#To get available architectures, just check arch/ directory

CC=x86_64-elf-gcc
AS=nasm
TARGET=redplanet.elf

C_SRC := $(shell find . -type f -name *.c)
AS_SRC := $(shell find . -type f -name *.asm)
OBJ := $(C_SRC:.c=.o) $(AS_SRC:.asm=.o)

CFLAGS=-Iinclude -ffreestanding -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2
LDFLAGS=-ffreestanding -nostdlib -lgcc
ASFLAGS=-f elf64

.PHONY: all iso run clean

all: $(TARGET) clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.asm
	$(AS) $(ASFLAGS) $< -o $@

$(TARGET): $(OBJ)
	$(CC) -T arch/linker.ld $(LDFLAGS) $^ -o $@

iso: $(TARGET)
	@mv redplanet.elf iso/boot
	@grub-mkrescue -o redplanet.iso iso

run: $(TARGET) iso clean
	@qemu-system-x86_64 redplanet.iso -m 64M -serial stdio -d int -no-reboot -no-shutdown

clean:
	@rm $(OBJ)