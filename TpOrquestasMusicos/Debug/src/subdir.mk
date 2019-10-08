################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/TpOrquestasMusicos.c \
../src/instrumentos.c \
../src/musicos.c \
../src/orquestas.c \
../src/utn.c 

OBJS += \
./src/TpOrquestasMusicos.o \
./src/instrumentos.o \
./src/musicos.o \
./src/orquestas.o \
./src/utn.o 

C_DEPS += \
./src/TpOrquestasMusicos.d \
./src/instrumentos.d \
./src/musicos.d \
./src/orquestas.d \
./src/utn.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


