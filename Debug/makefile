################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS

GEN_OPTS__FLAG := --cmd_file="C:/Users/user/workspace_v10/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs/Debug/configPkg/compiler.opt"
GEN_CMDS__FLAG := -l"C:/Users/user/workspace_v10/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs/Debug/configPkg/linker.cmd"

ORDERED_OBJS += \
"./CC2640R2_LAUNCHXL.obj" \
"./ccfg.obj" \
"./main_tirtos.obj" \
"./uartecho.obj" \
"../CC2640R2_LAUNCHXL_TIRTOS.cmd" \
$(GEN_CMDS__FLAG) \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/display/lib/display.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/mw/lcd/lib/lcd.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/grlib/lib/grlib.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/drivers/rf/lib/rf_multiMode_cc26x0r2.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/drivers/lib/drivers_cc26x0r2.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/drivers/pdm/lib/pdm_cc26x0r2.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/kernel/tirtos/packages/ti/dpl/lib/dpl_cc26x0r2.aem3" \
-l"C:/ti/simplelink_cc2640r2_sdk_1_40_00_45/source/ti/devices/cc26x0r2/driverlib/bin/ccs/driverlib.lib" \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.out \

EXE_OUTPUTS__QUOTED += \
"uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.out" \

BIN_OUTPUTS += \
uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.hex \

BIN_OUTPUTS__QUOTED += \
"uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.out"

dependents:
	-cd C:/Users/user/workspace_v10/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs/Debug && $(MAKE) all

# Tool invocations
uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) C:/Users/user/workspace_v10/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs/Debug/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: ARM Linker'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/bin/armcl" -mv7M3 --code_state=16 --float_support=vfplib -me --define=DeviceFamily_CC26X0R2 -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on -z -m"uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.map" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/lib" -i"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/include" --reread_libs --diag_wrap=off --display_error_number --warn_sections --xml_link_info="uartecho_CC2640R2_LAUNCHXL_tirtos_ccs_linkInfo.xml" --rom_model -o "uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: ARM Hex Utility'
	"C:/ti/ccs930/ccs/tools/compiler/ti-cgt-arm_18.12.5.LTS/bin/armhex"  -o "uartecho_CC2640R2_LAUNCHXL_tirtos_ccs.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "CC2640R2_LAUNCHXL.obj" "ccfg.obj" "main_tirtos.obj" "uartecho.obj" 
	-$(RM) "CC2640R2_LAUNCHXL.d" "ccfg.d" "main_tirtos.d" "uartecho.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
C:/Users/user/workspace_v10/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs/Debug/tirtos_builds_CC2640R2_LAUNCHXL_release_ccs.lib:

-include ../makefile.targets

