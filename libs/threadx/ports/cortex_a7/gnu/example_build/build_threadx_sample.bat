arm-none-eabi-gcc -c -g -mcpu=cortex-a7 reset.S
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 crt0.S
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 tx_initialize_low_level.S
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 MP_GIC.s
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 MP_PrivateTimer.s
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 V7.s
arm-none-eabi-gcc -c -g -mcpu=cortex-a7 -I../../../../common/inc -I../inc sample_threadx.c
arm-none-eabi-gcc -g -nostartfiles -mcpu=cortex-a7 -T sample_threadx.ld --specs=nosys.specs -o sample_threadx.out -Wl,-Map=sample_threadx.map MP_GIC.o MP_PrivateTimer.o V7.o crt0.o reset.o tx_initialize_low_level.o sample_threadx.o tx.a
