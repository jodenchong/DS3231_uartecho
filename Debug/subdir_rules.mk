################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --include_path="C:/Users/user/workspace_v10/uartecho_CC2640R2_LAUNCHXL_tirtos_ccs" --include_path="C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/kernel/tirtos/packages/ti/sysbios/posix" --include_path="C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/include" --define=DeviceFamily_CC26X0R2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


