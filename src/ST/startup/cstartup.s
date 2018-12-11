;/*
;********************************************************************************************************
;                                    EXCEPTION VECTORS & STARTUP CODE
;
; File      : cstartup.s
; For       : ARMv7M Cortex-M4
; Mode      : Thumb2
; Toolchain : RealView Development Suite
;             RealView Microcontroller Development Kit (MDK)
;             ARM Developer Suite (ADS)
;             Keil uVision
;********************************************************************************************************
;*/

;/*
;********************************************************************************************************
;*                           <<< Use Configuration Wizard in Context Menu >>>
;*
;* Note(s) : (1) The µVision4 Configuration Wizard enables menu driven configuration of assembler, 
;*               C/C++, or debugger initialization files. The Configuration Wizard uses control items 
;*               that are embedded into the comments of the configuration file.
;*
;********************************************************************************************************
;*/

;/*
;********************************************************************************************************
;*                                              STACK DEFINITIONS
;*
;* Configuration Wizard Menu:
;* // <h> Stack Configuration
;* //   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;* // </h>;
;*********************************************************************************************************
;*/

STACK_SIZE      EQU     0x00000400
                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   STACK_SIZE
__initial_sp


;/*
;********************************************************************************************************
;*                                              STACK DEFINITIONS
; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>
;*********************************************************************************************************
;*/

HEAP_SIZE       EQU     0x00000200
                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   HEAP_SIZE
__heap_limit


                PRESERVE8
                THUMB


                                                      ; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                IMPORT  SYS_IntHandlerWWDG
                IMPORT  SYS_IntHandlerPVD 
                IMPORT  SYS_IntHandlerTAMP_STAMP
                IMPORT  SYS_IntHandlerRTC_WKUP
                IMPORT  SYS_IntHandlerFLASH
                IMPORT  SYS_IntHandlerRCC
                IMPORT  SYS_IntHandlerEXTI0
                IMPORT  SYS_IntHandlerEXTI1
                IMPORT  SYS_IntHandlerEXTI2
                IMPORT  SYS_IntHandlerEXTI3
                IMPORT  SYS_IntHandlerEXTI4
                IMPORT  SYS_IntHandlerDMA1_CH0
                IMPORT  SYS_IntHandlerDMA1_CH1
                IMPORT  SYS_IntHandlerDMA1_CH2
                IMPORT  SYS_IntHandlerDMA1_CH3
                IMPORT  SYS_IntHandlerDMA1_CH4
                IMPORT  SYS_IntHandlerDMA1_CH5
                IMPORT  SYS_IntHandlerDMA1_CH6
                IMPORT  SYS_IntHandlerADC
                IMPORT  SYS_IntHandlerCAN1_TX
                IMPORT  SYS_IntHandlerCAN1_RX0
                IMPORT  SYS_IntHandlerCAN1_RX1
                IMPORT  SYS_IntHandlerCAN1_SCE
                IMPORT  SYS_IntHandlerEXTI9_5
                IMPORT  SYS_IntHandlerTIM1_BRK_TIM9
                IMPORT  SYS_IntHandlerTIM1_UP_TIM10
                IMPORT  SYS_IntHandlerTIM1_TRG_COM_TIM11
                IMPORT  SYS_IntHandlerTIM1_CC
                IMPORT  SYS_IntHandlerTIM2
                IMPORT  SYS_IntHandlerTIM3
                IMPORT  SYS_IntHandlerTIM4
                IMPORT  SYS_IntHandlerI2C1_EV
                IMPORT  SYS_IntHandlerI2C1_ER
                IMPORT  SYS_IntHandlerI2C2_EV
                IMPORT  SYS_IntHandlerI2C2_ER
                IMPORT  SYS_IntHandlerSPI1
                IMPORT  SYS_IntHandlerSPI2
                IMPORT  SYS_IntHandlerUSART1
                IMPORT  SYS_IntHandlerUSART2
                IMPORT  SYS_IntHandlerUSART3
                IMPORT  SYS_IntHandlerEXTI15_10
                IMPORT  SYS_IntHandlerRTCAlarm
                IMPORT  SYS_IntHandlerOTG_FS_WKUP
                IMPORT  SYS_IntHandlerTIM8_BRK_TIM12
                IMPORT  SYS_IntHandlerTIM8_UP_TIM13
                IMPORT  SYS_IntHandlerTIM8_TRG_COM_TIM14
                IMPORT  SYS_IntHandlerTIM8_CC
                IMPORT  SYS_IntHandlerDMA1_STREAM7
                IMPORT  SYS_IntHandlerFSMC
                IMPORT  SYS_IntHandlerSDIO
                IMPORT  SYS_IntHandlerTIM5
                IMPORT  SYS_IntHandlerSPI3
                IMPORT  SYS_IntHandlerUSART4
                IMPORT  SYS_IntHandlerUSART5
                IMPORT  SYS_IntHandlerTIM6_DAC
                IMPORT  SYS_IntHandlerTIM7
                IMPORT  SYS_IntHandlerDMA2_CH0
                IMPORT  SYS_IntHandlerDMA2_CH1
                IMPORT  SYS_IntHandlerDMA2_CH2
                IMPORT  SYS_IntHandlerDMA2_CH3
                IMPORT  SYS_IntHandlerDMA2_CH4
                IMPORT  SYS_IntHandlerETH
                IMPORT  SYS_IntHandlerETHWakeup
                IMPORT  SYS_IntHandlerCAN2_TX
                IMPORT  SYS_IntHandlerCAN2_RX0
                IMPORT  SYS_IntHandlerCAN2_RX1
                IMPORT  SYS_IntHandlerCAN2_SCE
                IMPORT  SYS_IntHandlerOTG_FS
                IMPORT  SYS_IntHandlerDMA2_CH5
                IMPORT  SYS_IntHandlerDMA2_CH6
                IMPORT  SYS_IntHandlerDMA2_CH7
                IMPORT  SYS_IntHandlerUSART6
                IMPORT  SYS_IntHandlerI2C3_EV
                IMPORT  SYS_IntHandlerI2C3_ER
                IMPORT  SYS_IntHandlerOTG_HS_EP1_OUT
                IMPORT  SYS_IntHandlerOTG_HS_EP1_IN
                IMPORT  SYS_IntHandlerOTG_HS_WKUP
                IMPORT  SYS_IntHandlerOTG_HS
                IMPORT  SYS_IntHandlerDCMI
                IMPORT  SYS_IntHandlerCRYP
                IMPORT  SYS_IntHandlerHASH_RNG
                IMPORT  SYS_IntHandlerFPU
				IMPORT  SYS_IntHandlerUART7               
                IMPORT  SYS_IntHandlerUART8              
                IMPORT  SYS_IntHandlerSPI4                
                IMPORT  SYS_IntHandlerSPI5                
                IMPORT  SYS_IntHandlerSPI6                
                IMPORT  SYS_IntHandlerSAI1                
                IMPORT  SYS_IntHandlerLTDC                
                IMPORT  SYS_IntHandlerLTDC_ER             
                IMPORT  SYS_IntHandlerDMA2D 

                IMPORT  OS_CPU_PendSVHandler
                IMPORT  OS_CPU_SysTickHandler 

__Vectors       DCD     __initial_sp                      ; Top of Stack
                DCD     Reset_Handler                     ; Reset Handler
                DCD     App_NMI_ISR                       ; NMI Handler
                DCD     App_Fault_ISR                     ; Hard Fault Handler
                DCD     App_MemFault_ISR                  ; MPU Fault Handler
                DCD     App_BusFault_ISR                  ; Bus Fault Handler
                DCD     App_UsageFault_ISR                ; Usage Fault Handler
                DCD     App_Spurious_ISR                  ; Reserved
                DCD     App_Spurious_ISR                  ; Reserved
                DCD     App_Spurious_ISR                  ; Reserved
                DCD     App_Spurious_ISR                  ; Reserved
                DCD     App_Spurious_ISR                  ; SVCall Handler
                DCD     App_Spurious_ISR                  ; Debug Monitor Handler
                DCD     App_Spurious_ISR                  ; Reserved
                DCD     OS_CPU_PendSVHandler              ; PendSV Handler
                DCD     OS_CPU_SysTickHandler             ; SysTick Handler

                                                          ;  External Interrupts
                DCD     SYS_IntHandlerWWDG                ; 16, INTISR[  0]  Window Watchdog.
                DCD     SYS_IntHandlerPVD                 ; 17, INTISR[  1]  PVD through EXTI Line Detection.
                DCD     SYS_IntHandlerTAMP_STAMP          ; 18, INTISR[  2]  Tamper and TimeStamp Interrupt.
                DCD     SYS_IntHandlerRTC_WKUP            ; 19, INTISR[  3]  RTC Wakeup Global Interrupt.
                DCD     SYS_IntHandlerFLASH               ; 20, INTISR[  4]  FLASH Global Interrupt.
                DCD     SYS_IntHandlerRCC                 ; 21, INTISR[  5]  RCC Global Interrupt.
                DCD     SYS_IntHandlerEXTI0               ; 22, INTISR[  6]  EXTI Line0 Interrupt.
                DCD     SYS_IntHandlerEXTI1               ; 23, INTISR[  7]  EXTI Line1 Interrupt.
                DCD     SYS_IntHandlerEXTI2               ; 24, INTISR[  8]  EXTI Line2 Interrupt.
                DCD     SYS_IntHandlerEXTI3               ; 25, INTISR[  9]  EXTI Line3 Interrupt.
                DCD     SYS_IntHandlerEXTI4               ; 26, INTISR[ 10]  EXTI Line4 Interrupt.
                DCD     SYS_IntHandlerDMA1_CH0            ; 27, INTISR[ 11]  DMA Channel0 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH1            ; 28, INTISR[ 12]  DMA Channel1 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH2            ; 29, INTISR[ 13]  DMA Channel2 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH3            ; 30, INTISR[ 14]  DMA Channel3 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH4            ; 31, INTISR[ 15]  DMA Channel4 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH5            ; 32, INTISR[ 16]  DMA Channel5 Global Interrupt.
                DCD     SYS_IntHandlerDMA1_CH6            ; 33, INTISR[ 17]  DMA Channel6 Global Interrupt.
                DCD     SYS_IntHandlerADC                 ; 34, INTISR[ 18]  ADC1, ADC2 & ADC3 Global Interrupt.
                DCD     SYS_IntHandlerCAN1_TX             ; 35, INTISR[ 19]  CAN1 TX  Interrupts.
                DCD     SYS_IntHandlerCAN1_RX0            ; 36, INTISR[ 20]  CAN1 RX0 Interrupts.
                DCD     SYS_IntHandlerCAN1_RX1            ; 37, INTISR[ 21]  CAN1 RX1 Interrupt.
                DCD     SYS_IntHandlerCAN1_SCE            ; 38, INTISR[ 22]  CAN1 SCE Interrupt.
                DCD     SYS_IntHandlerEXTI9_5             ; 39, INTISR[ 23]  EXTI Line[9:5] Interrupt.
                DCD     SYS_IntHandlerTIM1_BRK_TIM9       ; 40, INTISR[ 24]  TIM1 Break  Interrupt & TIM9 Glb int.
                DCD     SYS_IntHandlerTIM1_UP_TIM10       ; 41, INTISR[ 25]  TIM1 Update Interrupt & TIM10 Glb int.
                DCD     SYS_IntHandlerTIM1_TRG_COM_TIM11  ; 42, INTISR[ 26]  TIM1 Trig & Commutation Interrupts...
                                                          ; .................and TIM11 global interrupt.
                                                                
                DCD     SYS_IntHandlerTIM1_CC             ; 43, INTISR[ 27]  TIM1 Capture Compare Interrupt.
                DCD     SYS_IntHandlerTIM2                ; 44, INTISR[ 28]  TIM2 Global Interrupt.
                DCD     SYS_IntHandlerTIM3                ; 45, INTISR[ 29]  TIM3 Global Interrupt.
                DCD     SYS_IntHandlerTIM4                ; 46, INTISR[ 30]  TIM4 Global Interrupt.
                DCD     SYS_IntHandlerI2C1_EV             ; 47, INTISR[ 31]  I2C1 Event  Interrupt.
                DCD     SYS_IntHandlerI2C1_ER             ; 48, INTISR[ 32]  I2C1 Error  Interrupt.
                DCD     SYS_IntHandlerI2C2_EV             ; 49, INTISR[ 33]  I2C2 Event  Interrupt.
                DCD     SYS_IntHandlerI2C2_ER             ; 50, INTISR[ 34]  I2C2 Error  Interrupt.
                DCD     SYS_IntHandlerSPI1                ; 51, INTISR[ 35]  SPI1 Global Interrupt.
                DCD     SYS_IntHandlerSPI2                ; 52, INTISR[ 36]  SPI2 Global Interrupt.
                DCD     SYS_IntHandlerUSART1              ; 53, INTISR[ 37]  USART1 Global Interrupt.
                DCD     SYS_IntHandlerUSART2              ; 54, INTISR[ 38]  USART2 Global Interrupt.
                DCD     SYS_IntHandlerUSART3              ; 55, INTISR[ 39]  USART3 Global Interrupt.
                DCD     SYS_IntHandlerEXTI15_10           ; 56, INTISR[ 40]  EXTI Line [15:10] Interrupts.
                DCD     SYS_IntHandlerRTCAlarm            ; 57, INTISR[ 41]  RTC Alarm EXT Line Interrupt.
                DCD     SYS_IntHandlerOTG_FS_WKUP         ; 58, INTISR[ 42]  USB OTG Wakeup through EXTI line int.
                DCD     SYS_IntHandlerTIM8_BRK_TIM12      ; 59, INTISR[ 43]  TIM8 Break and TIM12 global Int.
                DCD     SYS_IntHandlerTIM8_UP_TIM13       ; 60, INTISR[ 44]  TIM8 Update and TIM13 global Int.
                DCD     SYS_IntHandlerTIM8_TRG_COM_TIM14  ; 61, INTISR[ 45]  TIM8 Trigger/Commutation and TIM14.
                DCD     SYS_IntHandlerTIM8_CC             ; 62, INTISR[ 46]  TIM8 Capture Compare Int.
                DCD     SYS_IntHandlerDMA1_STREAM7        ; 63, INTISR[ 47]  DMA1 Stream7 Interrupt.
                DCD     SYS_IntHandlerFSMC                ; 64, INTISR[ 48]  FMC global Interrupt.
                DCD     SYS_IntHandlerSDIO                ; 65, INTISR[ 49]  SDIO global Interrupt.
                DCD     SYS_IntHandlerTIM5                ; 66, INTISR[ 50]  TIM5 global Interrupt. 
                DCD     SYS_IntHandlerSPI3                ; 67, INTISR[ 51]  SPI3 global Interrupt.
                DCD     SYS_IntHandlerUSART4              ; 68, INTISR[ 52]  UART4 global Interrupt.
                DCD     SYS_IntHandlerUSART5              ; 69, INTISR[ 53]  UART5 global Interrupt.
                DCD     SYS_IntHandlerTIM6_DAC            ; 70, INTISR[ 54]  TIM6 global Interrupt, DAC1 & DAC2 ..
                                                          ; ................ underrun error interrupts.
                                                                
                DCD     SYS_IntHandlerTIM7                ; 71, INTISR[ 55]  TIM7 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH0            ; 72, INTISR[ 56]  DMA2 Channel 0 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH1            ; 73, INTISR[ 57]  DMA2 Channel 1 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH2            ; 74, INTISR[ 58]  DMA2 Channel 2 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH3            ; 75, INTISR[ 59]  DMA2 Channel 3 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH4            ; 76, INTISR[ 60]  DMA2 Channel 4 global Interrupt.
                DCD     SYS_IntHandlerETH                 ; 77, INTISR[ 61]  ETH global Interrupt.
                DCD     SYS_IntHandlerETHWakeup           ; 78, INTISR[ 62]  ETH WakeUp from EXTI line Interrupt.
                DCD     SYS_IntHandlerCAN2_TX             ; 79, INTISR[ 63]  CAN2 TX Interrupts.
                DCD     SYS_IntHandlerCAN2_RX0            ; 80, INTISR[ 64]  CAN2 RX0 Interrupts.
                DCD     SYS_IntHandlerCAN2_RX1            ; 81, INTISR[ 65]  CAN2 RX1 Interrupt.
                DCD     SYS_IntHandlerCAN2_SCE            ; 82, INTISR[ 66]  CAN2 SCE Interrupt.
                DCD     SYS_IntHandlerOTG_FS              ; 83, INTISR[ 67]  OTG global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH5            ; 84, INTISR[ 68]  DMA2 Channel 5 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH6            ; 85, INTISR[ 69]  DMA2 Channel 6 global Interrupt.
                DCD     SYS_IntHandlerDMA2_CH7            ; 86, INTISR[ 70]  DMA2 Channel 7 global Interrupt.
                DCD     SYS_IntHandlerUSART6              ; 87, INTISR[ 71]  UART6 global Interrupt.
                DCD     SYS_IntHandlerI2C3_EV             ; 88, INTISR[ 72]  I2C3 Event  Interrupt.
                DCD     SYS_IntHandlerI2C3_ER             ; 89, INTISR[ 73]  I2C3 Error  Interrupt.
                DCD     SYS_IntHandlerOTG_HS_EP1_OUT      ; 90, INTISR[ 74]  OTG HS EP1 OUT Interrupt.
                DCD     SYS_IntHandlerOTG_HS_EP1_IN       ; 91, INTISR[ 75]  OTG HS EP1 IN Interrupt.
                DCD     SYS_IntHandlerOTG_HS_WKUP         ; 92, INTISR[ 76]  OTG HS Wakeup Interrupt.
                DCD     SYS_IntHandlerOTG_HS              ; 93, INTISR[ 77]  OTG HS global Interrupt.
                DCD     SYS_IntHandlerDCMI                ; 94, INTISR[ 78]  DCMI global Interrupt.
                DCD     SYS_IntHandlerCRYP                ; 95, INTISR[ 79]  CRYPT crypto global Interrupt.
                DCD     SYS_IntHandlerHASH_RNG            ; 96, INTISR[ 80]  HASH and RNG global Interrupt.
                DCD     SYS_IntHandlerFPU                 ; 97, INTISR[ 81]  FPU global Interrupt.
                DCD     SYS_IntHandlerUART7               ; 98, INTISR[ 82]  UART7 global Interrupt.
                DCD     SYS_IntHandlerUART8               ; 98, INTISR[ 83]  UART8 global Interrupt.
                DCD     SYS_IntHandlerSPI4                ; 99, INTISR[ 84]  SPI4 global Interrupt.
                DCD     SYS_IntHandlerSPI5                ;100, INTISR[ 85]  SPI5 global Interrupt.
                DCD     SYS_IntHandlerSPI6                ;101, INTISR[ 86]  SPI6 global Interrupt.
                DCD     SYS_IntHandlerSAI1                ;102, INTISR[ 87]  SAI1 global Interrupt.
                DCD     SYS_IntHandlerLTDC                ;103, INTISR[ 88]  LTDC global Interrupt.
                DCD     SYS_IntHandlerLTDC_ER             ;104, INTISR[ 89]  LTDC ERROR global Interrupt.
                DCD     SYS_IntHandlerDMA2D               ;105, INTISR[ 90]  DMA2D global Interrupt.


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC    
                EXPORT  Reset_Handler                 [WEAK]
                IMPORT  __main

                IF {FPU} != "SoftVFP"
                                                ; Enable Floating Point Support at reset for FPU
                LDR.W   R0, =0xE000ED88         ; Load address of CPACR register
                LDR     R1, [R0]                ; Read value at CPACR
                ORR     R1,  R1, #(0xF <<20)    ; Set bits 20-23 to enable CP10 and CP11 coprocessors
                                                ; Write back the modified CPACR value
                STR     R1, [R0]                ; Wait for store to complete
                DSB
                
                                                ; Disable automatic FP register content
                                                ; Disable lazy context switch
                LDR.W   R0, =0xE000EF34         ; Load address to FPCCR register
                LDR     R1, [R0]
                AND     R1,  R1, #(0x3FFFFFFF)  ; Clear the LSPEN and ASPEN bits
                STR     R1, [R0]
                ISB                             ; Reset pipeline now the FPU is enabled
                ENDIF

                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)                

App_NMI_ISR      PROC
                EXPORT  App_NMI_ISR                   [WEAK]
                B       .
                ENDP
App_Fault_ISR\
                PROC
                EXPORT  App_Fault_ISR                 [WEAK]
                B       .
                ENDP
App_MemFault_ISR\
                PROC
                EXPORT  App_MemFault_ISR             [WEAK]
                B       .
                ENDP
App_BusFault_ISR\
                PROC
                EXPORT  App_BusFault_ISR             [WEAK]
                B       .
                ENDP
App_UsageFault_ISR\
                PROC
                EXPORT  App_UsageFault_ISR            [WEAK]
                B       .
                ENDP
App_Spurious_ISR\
                PROC
                EXPORT  App_Spurious_ISR                [WEAK]
                B       .
                ENDP
App_Reserved_ISR\
                PROC
                EXPORT  App_Reserved_ISR                [WEAK]
                B       .
                ENDP


                ALIGN


                                                                ; User Initial Stack & Heap

                IF      :DEF:__MICROLIB
                
                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit
                
                ELSE
                
                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + STACK_SIZE)
                LDR     R2, =(Heap_Mem  +  HEAP_SIZE)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
