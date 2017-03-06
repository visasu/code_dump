################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
freertos_demo.obj: ../freertos_demo.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="freertos_demo.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

led_task.obj: ../led_task.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="led_task.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

startup_ccs.obj: ../startup_ccs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="startup_ccs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

switch_task.obj: ../switch_task.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Compiler'
	"C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 --abi=eabi -me -O2 --include_path="C:/TI/ccsv6/tools/compiler/ti-cgt-arm_15.12.1.LTS/include" --include_path="//VBOXSVR/FreeRTOS/CodeComposer/freertos_demo" --include_path="//examples/boards/ek-tm4c123gxl" --include_path="//" --include_path="//third_party" --include_path="//third_party/FreeRTOS/Source/include" --include_path="//third_party/FreeRTOS" --include_path="//third_party/FreeRTOS/Source/portable/CCS/ARM_CM4F" --advice:power=all -g --gcc --define=ccs="ccs" --define=PART_TM4C123GH6PM --define=TARGET_IS_TM4C123_RB1 --diag_wrap=off --diag_warning=225 --display_error_number --gen_func_subsections=on --ual --preproc_with_compile --preproc_dependency="switch_task.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


