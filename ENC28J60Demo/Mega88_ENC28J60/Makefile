# makefile, written by guido socher
MCU=atmega168
#MCU=atmega88
# note you can also change below prg_load_uc_88 to prg_load_uc_168 if
# you use the atmega168 and write programs that are too big for atmega88
CC=avr-gcc
OBJCOPY=avr-objcopy
# optimize for size:
CFLAGS=-g -mmcu=$(MCU) -Wall -Wstrict-prototypes -Os -mcall-prologues
#-------------------
.PHONY: test0 test1 test2 all
#
all: eth_rem_dev_tcp.hex test0.hex test1.hex test2.hex test_readSiliconRev.hex
#
test0: test0.hex
#
test1: test1.hex 
#
test2: test2.hex
#
#-------------------
help: 
	@echo "Usage: make all|test0.hex|test1.hex|test2.hex|load|load_test0|load_test1|load_test2|rdfuses"
	@echo "or"
	@echo "Usage: make clean"
	@echo " "
	@echo "For new hardware with clock from enc38j60: make fuse"
#-------------------
eth_rem_dev_tcp.hex : eth_rem_dev_tcp.out 
	$(OBJCOPY) -R .eeprom -O ihex eth_rem_dev_tcp.out eth_rem_dev_tcp.hex 
	avr-size eth_rem_dev_tcp.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "

eth_rem_dev_tcp.out : main.o ip_arp_udp_tcp.o enc28j60.o timeout.o
	$(CC) $(CFLAGS) -o eth_rem_dev_tcp.out -Wl,-Map,eth_rem_dev_tcp.map main.o ip_arp_udp_tcp.o enc28j60.o timeout.o
enc28j60.o : enc28j60.c avr_compat.h timeout.h enc28j60.h
	$(CC) $(CFLAGS) -Os -c enc28j60.c
ip_arp_udp_tcp.o : ip_arp_udp_tcp.c net.h avr_compat.h enc28j60.h
	$(CC) $(CFLAGS) -Os -c ip_arp_udp_tcp.c
main.o : main.c ip_arp_udp_tcp.h avr_compat.h enc28j60.h timeout.h net.h
	$(CC) $(CFLAGS) -Os -c main.c
timeout.o : timeout.c timeout.h 
	$(CC) $(CFLAGS) -Os -c timeout.c
#------------------
test0.hex : test0.out 
	$(OBJCOPY) -R .eeprom -O ihex test0.out test0.hex 
	avr-size test0.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
test0.out : test0.o 
	$(CC) $(CFLAGS) -o test0.out -Wl,-Map,test0.map test0.o 
test0.o : test0.c 
	$(CC) $(CFLAGS) -Os -c test0.c
#------------------
test2.hex : test2.out 
	$(OBJCOPY) -R .eeprom -O ihex test2.out test2.hex 
	avr-size test2.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
test2.out : test2.o enc28j60.o timeout.o ip_arp_udp_tcp.o
	$(CC) $(CFLAGS) -o test2.out -Wl,-Map,test2.map test2.o enc28j60.o timeout.o ip_arp_udp_tcp.o
test2.o : test2.c ip_arp_udp_tcp.h avr_compat.h enc28j60.h timeout.h net.h
	$(CC) $(CFLAGS) -Os -c test2.c
#------------------
test1.hex : test1.out 
	$(OBJCOPY) -R .eeprom -O ihex test1.out test1.hex 
	avr-size test1.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
test1.out : test1.o enc28j60.o timeout.o ip_arp_udp_tcp.o
	$(CC) $(CFLAGS) -o test1.out -Wl,-Map,test1.map test1.o enc28j60.o timeout.o ip_arp_udp_tcp.o
test1.o : test1.c ip_arp_udp_tcp.h avr_compat.h enc28j60.h timeout.h net.h
	$(CC) $(CFLAGS) -Os -c test1.c
#------------------
test_readSiliconRev.hex : test_readSiliconRev.out 
	$(OBJCOPY) -R .eeprom -O ihex test_readSiliconRev.out test_readSiliconRev.hex 
	avr-size test_readSiliconRev.out
	@echo " "
	@echo "Expl.: data=initialized data, bss=uninitialized data, text=code"
	@echo " "
test_readSiliconRev.out : test_readSiliconRev.o enc28j60.o timeout.o ip_arp_udp_tcp.o
	$(CC) $(CFLAGS) -o test_readSiliconRev.out -Wl,-Map,test_readSiliconRev.map test_readSiliconRev.o enc28j60.o timeout.o ip_arp_udp_tcp.o
test_readSiliconRev.o : test_readSiliconRev.c ip_arp_udp_tcp.h avr_compat.h enc28j60.h timeout.h net.h
	$(CC) $(CFLAGS) -Os -c test_readSiliconRev.c
#------------------
#------------------
load_test2: test2.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 test2.hex
else
	./prg_load_uc_168 test2.hex
endif
#
load_readSiliconRev: test_readSiliconRev.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 test_readSiliconRev.hex
else
	./prg_load_uc_168 test_readSiliconRev.hex
endif
#
load_test1: test1.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 test1.hex
else
	./prg_load_uc_168 test1.hex
endif
#
load_test0: test0.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 test0.hex
else
	./prg_load_uc_168 test0.hex
endif
#------------------
load: eth_rem_dev_tcp.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 eth_rem_dev_tcp.hex
else
	./prg_load_uc_168 eth_rem_dev_tcp.hex
endif
#
loaduisp: eth_rem_dev_tcp.hex
ifeq ($(MCU),atmega88)
	./prg_load_uc_88 -u eth_rem_dev_tcp.hex
else
	./prg_load_uc_168 -u eth_rem_dev_tcp.hex
endif
#-------------------
# Check this with make rdfuses
rdfuses:
ifeq ($(MCU),atmega88)
	./prg_fusebit_uc_88 -r
else
	./prg_fusebit_uc_168 -r
endif
#
fuse:
	@echo "warning: run this command only if you have an external clock on xtal1"
	@echo "The is the last chance to stop. Press crtl-C to abort"
	@sleep 2
ifeq ($(MCU),atmega88)
	./prg_fusebit_uc_88 -w 0x60
else
	./prg_fusebit_uc_168 -w 0x60
endif
#-------------------
clean:
	rm -f *.o *.map *.out test*.hex eth_rem_dev_tcp.hex
#-------------------
