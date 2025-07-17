################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-armllvm_3.2.2.LTS/bin/tiarmclang.exe" -c @"device.opt"  -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O2 -I"D:/vidyaleap ccs/timx_timer_mode_periodic_standby_LP_MSPM0G3507_nortos_ticlang" -I"D:/vidyaleap ccs/timx_timer_mode_periodic_standby_LP_MSPM0G3507_nortos_ticlang/Debug" -I"/source/third_party/CMSIS/Core/Include" -I"/source" -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)"  $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

error.h: ../timx_timer_mode_periodic_standby.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"C:/ti/sysconfig_1.22.0/sysconfig_cli.bat" --script "D:/vidyaleap ccs/timx_timer_mode_periodic_standby_LP_MSPM0G3507_nortos_ticlang/timx_timer_mode_periodic_standby.syscfg" -o "." --compiler ticlang
	@echo 'Finished building: "$<"'
	@echo ' '


