# Red Planet
Red Planet is an operating system written entirely from scratch targetting x86 platform. That means it doesn't use Linux, BSD or any existing kernel as a core - it uses it's own kernel. Red Planet doesn't follow POSIX standard meaning **it's not an UNIX like or UNIX based system**. It borrows some features from UNIX or Linux, or even Windows, but it's not another UNIX clone or even a Windows clone.

# Building

## Prerequisties to build

* [i686-elf-gcc](https://github.com/lordmilko/i686-elf-tools)
* CMake
* GNU Make

If you're using Ubuntu 22.04 (or latest 24.04) then you can run this command to install all necessary software (apart from i686-elf-gcc)
```console
# apt install cmake make xorriso mtools grub-pc-bin qemu-system-x86
```

## Instructions

In project' root directory run:
```console
mkdir build && cd build && cmake .. && make
```

Now, to just run generated binary in QEMU, run:
```console
make qemu-run
```

You can also build an ISO using:
```console
make grub-iso
```

The ISO is located in build directory