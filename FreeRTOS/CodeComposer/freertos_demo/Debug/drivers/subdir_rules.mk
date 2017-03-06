################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
drivers/buttons.obj: C:/TI/TivaWare_C_Series-2.1.3.156/examples/boards/ek-tm4c123gxl/drivers/buttons.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="drivers/buttons.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

drivers/rgb.obj: C:/TI/TivaWare_C_Series-2.1.3.156/examples/boards/ek-tm4c123gxl/drivers/rgb.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="drivers/rgb.d" --obj_directory="drivers" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


