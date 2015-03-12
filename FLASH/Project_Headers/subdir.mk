################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Project_Headers/mag.c" \

C_SRCS += \
../Project_Headers/mag.c \

OBJS += \
./Project_Headers/mag_c.obj \

OBJS_QUOTED += \
"./Project_Headers/mag_c.obj" \

C_DEPS += \
./Project_Headers/mag_c.d \

OBJS_OS_FORMAT += \
./Project_Headers/mag_c.obj \

C_DEPS_QUOTED += \
"./Project_Headers/mag_c.d" \


# Each subdirectory must supply rules for building sources it contributes
Project_Headers/mag_c.obj: ../Project_Headers/mag.c
	@echo 'Building file: $<'
	@echo 'Executing target #14 $<'
	@echo 'Invoking: PowerPC Compiler'
	"$(PAToolsDirEnv)/mwcceppc" @@"Project_Headers/mag.args" -o "Project_Headers/mag_c.obj" "$<" -MD -gccdep
	@echo 'Finished building: $<'
	@echo ' '

Project_Headers/%.d: ../Project_Headers/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '


