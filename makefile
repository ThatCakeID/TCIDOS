COMPILER = gcc
LINKER = ld
ASSEMBLER = nasm
CFLAGS = -m32 -c -ffreestanding
ASFLAGS = -f elf32
LDFLAGS = -m elf_i386 -T src/link.ld
EMULATOR = qemu-system-i386
EMULATOR_FLAGS = -kernel

OBJS = obj/kasm.o obj/kc.o obj/idt.o obj/isr.o obj/kb.o obj/screen.o obj/string.o obj/system.o obj/util.o obj/shell.o obj/log.o
OUTPUT = tcidos/boot/kernel.bin

run: all
	$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

all:$(OBJS)
	mkdir tcidos/ -p
	mkdir tcidos/boot/ -p
	$(LINKER) $(LDFLAGS) -o $(OUTPUT) $(OBJS)

obj/kasm.o:src/kernel.asm
	$(ASSEMBLER) $(ASFLAGS) -o obj/kasm.o src/kernel.asm
	
obj/kc.o:src/kernel.c
	$(COMPILER) $(CFLAGS) src/kernel.c -o obj/kc.o 
	
obj/idt.o:src/idt.c
	$(COMPILER) $(CFLAGS) src/idt.c -o obj/idt.o 

obj/kb.o:src/kb.c
	$(COMPILER) $(CFLAGS) src/kb.c -o obj/kb.o

obj/isr.o:src/isr.c
	$(COMPILER) $(CFLAGS) src/isr.c -o obj/isr.o

obj/screen.o:src/screen.c
	$(COMPILER) $(CFLAGS) src/screen.c -o obj/screen.o

obj/string.o:src/string.c
	$(COMPILER) $(CFLAGS) src/string.c -o obj/string.o

obj/system.o:src/system.c
	$(COMPILER) $(CFLAGS) src/system.c -o obj/system.o

obj/util.o:src/util.c
	$(COMPILER) $(CFLAGS) src/util.c -o obj/util.o
	
obj/shell.o:src/shell.c
	$(COMPILER) $(CFLAGS) src/shell.c -o obj/shell.o

obj/log.o:src/log.c
	$(COMPILER) $(CFLAGS) src/log.c - o obj/log.o

build:all
	#Activate the install xorr if you do not have it already installed
	#sudo apt-get install xorriso
	rm tcidos/boot/grub/ -r -f
	mkdir tcidos/boot/grub/
	echo set default=0 >> tcidos/boot/grub/grub.cfg
	echo set timeout=0 >> tcidos/boot/grub/grub.cfg
	echo menuentry "TCIDOS" { >> tcidos/boot/grub/grub.cfg
	#echo         set root='(hd96)' >> tcidos/boot/grub/grub.cfg
	echo         multiboot /boot/kernel.bin >> tcidos/boot/grub/grub.cfg
	echo } >> tcidos/boot/grub/grub.cfg

	grub-mkrescue -o tcidos.iso tcidos/
	
clear:
	rm -f obj/*.o
	rm -r -f tcidos/
	
