/*******************************************************************************
 Copyright SAKC Corporation. 2016. All rights reserved.
--------------------------------------------------------------------------------
    File name    : sys_interrupt.h
    Project name : 公共可移植模块。
    Module name  : 
    Date created : 2017年8月17日   14时28分49秒
    Author       : Ning.JianLi
    Description  : STM32移植UCOS操作系统的中断处理部分。
*******************************************************************************/

#ifndef __SYS_INTERRUPT_H__
#define __SYS_INTERRUPT_H__

#include <stdio.h>
#include "pub_type.h"
#include "cpu.h"
#include "os.h"
#include "stm32f429_eth.h"

#ifdef __cplusplus
extern "c" {
#endif /* __cplusplus */


/* STM32F4XX 中断总数 */
#define SYS_INTERRUPT_TOTAL_NUM                            91

/* Window WatchDog Interrupt */
#define SYS_INT_ID_WWDG                                   0u

/* PVD through EXTI Line detection Interrupt */
#define SYS_INT_ID_PVD                                    1u   

/* Tamper and TimeStamp Interrupt */
#define SYS_INT_ID_TAMP_STAMP                             2u   

/* RTC wakeup Interrupt through the EXTI line */
#define SYS_INT_ID_RTC_WKUP                               3u   

/* FLASH global Interrupt */
#define SYS_INT_ID_FLASH                                  4u   

/* RCC global Interrupt */
#define SYS_INT_ID_RCC                                    5u   

/* EXTI Line0 Interrupt */
#define SYS_INT_ID_EXTI0                                  6u   

/* EXTI Line1 Interrupt */
#define SYS_INT_ID_EXTI1                                  7u   

/* EXTI Line2 Interrupt */
#define SYS_INT_ID_EXTI2                                  8u   

/* EXTI Line3 Interrupt */
#define SYS_INT_ID_EXTI3                                  9u   

/* EXTI Line4 Interrupt */
#define SYS_INT_ID_EXTI4                                 10u   

/* DMA1 Channel 0 global Interrupt */
#define SYS_INT_ID_DMA1_CH0                              11u   

/* DMA1 Channel 1 global Interrupt */
#define SYS_INT_ID_DMA1_CH1                              12u   

/* DMA1 Channel 2 global Interrupt */
#define SYS_INT_ID_DMA1_CH2                              13u   

/* DMA1 Channel 3 global Interrupt */
#define SYS_INT_ID_DMA1_CH3                              14u   

/* DMA1 Channel 4 global Interrupt */
#define SYS_INT_ID_DMA1_CH4                              15u   

/* DMA1 Channel 5 global Interrupt */
#define SYS_INT_ID_DMA1_CH5                              16u   

/* DMA1 Channel 6 global Interrupt */
#define SYS_INT_ID_DMA1_CH6                              17u   

/* ADC1, ADC2 and ADC3 global Interrupt */
#define SYS_INT_ID_ADC                                   18u   

/* CAN1 TX Interrupts */
#define SYS_INT_ID_CAN1_TX                               19u   

/* CAN1 RX0 Interrupts */
#define SYS_INT_ID_CAN1_RX0                              20u   

/* CAN1 RX1 Interrupt */
#define SYS_INT_ID_CAN1_RX1                              21u   

/* CAN1 SCE Interrupt */
#define SYS_INT_ID_CAN1_SCE                              22u   

/* External Line[9:5] Interrupts */
#define SYS_INT_ID_EXTI9_5                               23u   

/* TIM1 Break Interrupt and TIM9 global interrupt */
#define SYS_INT_ID_TIM1_BRK_TIM9                         24u   

/* TIM1 Update Interrupt and TIM10 global interrupt */
#define SYS_INT_ID_TIM1_UP_TIM10                         25u   

/* TIM1 Trigger & Commutation Int. & TIM11 global Int. */
#define SYS_INT_ID_TIM1_TRG_COM_TIM11                    26u   

/* TIM1 Capture Compare Interrupt */
#define SYS_INT_ID_TIM1_CC                               27u   

/* TIM2 global Interrupt */
#define SYS_INT_ID_TIM2                                  28u   

/* TIM3 global Interrupt */
#define SYS_INT_ID_TIM3                                  29u   

/* TIM4 global Interrupt */
#define SYS_INT_ID_TIM4                                  30u   

/* I2C1 Event Interrupt */
#define SYS_INT_ID_I2C1_EV                               31u   

/* I2C1 Error Interrupt */
#define SYS_INT_ID_I2C1_ER                               32u   

/* I2C2 Event Interrupt */
#define SYS_INT_ID_I2C2_EV                               33u   

/* I2C2 Error Interrupt */
#define SYS_INT_ID_I2C2_ER                               34u   

/* SPI1 global Interrupt */
#define SYS_INT_ID_SPI1                                  35u   

/* SPI2 global Interrupt */
#define SYS_INT_ID_SPI2                                  36u   

/* USART1 global Interrupt */
#define SYS_INT_ID_USART1                                37u   

/* USART2 global Interrupt */
#define SYS_INT_ID_USART2                                38u   

/* USART3 global Interrupt */
#define SYS_INT_ID_USART3                                39u   

/* External Line[15:10] Interrupts */
#define SYS_INT_ID_EXTI15_10                             40u   

/* RTC Alarms (A and B) through EXTI Line Interrupt */
#define SYS_INT_ID_RTC_ALARM                             41u   

/* USB WakeUp from suspend through EXTI Line Interrupt */
#define SYS_INT_ID_OTG_FS_WKUP                           42u   

/* TIM8 Break Interrupt and TIM12 global Interrupt */
#define SYS_INT_ID_TIM8_BRK_TIM12                        43u   

/* TIM8 Update Interrupt and TIM13 global Interrupt */
#define SYS_INT_ID_TIM8_UP_TIM13                         44u   

/* TIM8 Trigger/Commutation and TIM14 global Interrupt */
#define SYS_INT_ID_TIM8_TRG_COM_TIM14                    45u   

/* TIM8 Capture Compare Interrupt */
#define SYS_INT_ID_TIM8_CC                               46u   

/* DMA1 Stream7 Interrupt */
#define SYS_INT_ID_DMA1_STREAM7                          47u   

/* FSMC global Interrupt */
#define SYS_INT_ID_FSMC                                  48u   

/* SDIO global Interrupt */
#define SYS_INT_ID_SDIO                                  49u   

/* TIM5 global Interrupt */
#define SYS_INT_ID_TIM5                                  50u   

/* SPI3 global Interrupt */
#define SYS_INT_ID_SPI3                                  51u   

/* USART4 global Interrupt */
#define SYS_INT_ID_USART4                                52u   

/* USART5 global Interrupt */
#define SYS_INT_ID_USART5                                53u   

/* TIM6 global Interrupt, DAC1 & DAC2 underrun err int. */
#define SYS_INT_ID_TIM6_DAC                              54u   

/* TIM7 global Interrupt */
#define SYS_INT_ID_TIM7                                  55u   

/* DMA2 Channel 0 global Interrupt */
#define SYS_INT_ID_DMA2_CH0                              56u   

/* DMA2 Channel 1 global Interrupt */
#define SYS_INT_ID_DMA2_CH1                              57u   

/* DMA2 Channel 2 global Interrupt */
#define SYS_INT_ID_DMA2_CH2                              58u   

/* DMA2 Channel 3 global Interrupt */
#define SYS_INT_ID_DMA2_CH3                              59u   

/* DMA2 Channel 4 global Interrupt */
#define SYS_INT_ID_DMA2_CH4                              60u   

/* ETH  global Interrupt */
#define SYS_INT_ID_ETH                                   61u   

/* ETH  WakeUp from EXTI line interrupt */
#define SYS_INT_ID_ETH_WKUP                              62u   

/* CAN2 TX Interrupt */
#define SYS_INT_ID_CAN2_TX                               63u   

/* CAN2 RX0 Interrupt */
#define SYS_INT_ID_CAN2_RX0                              64u   

/* CAN2 RX1 Interrupt */
#define SYS_INT_ID_CAN2_RX1                              65u   

/* CAN2 SCE Interrupt */
#define SYS_INT_ID_CAN2_SCE                              66u   

/* OTG global Interrupt */
#define SYS_INT_ID_OTG_FS                                67u   

/* DMA2 Channel 5 global Interrupt */
#define SYS_INT_ID_DMA2_CH5                              68u   

/* DMA2 Channel 6 global Interrupt */
#define SYS_INT_ID_DMA2_CH6                              69u   

/* DMA2 Channel 7 global Interrupt */
#define SYS_INT_ID_DMA2_CH7                              70u   

/* USART6 global Interrupt */
#define SYS_INT_ID_USART6                                71u   

/* I2C3 Event  Interrupt */
#define SYS_INT_ID_I2C3_EV                               72u   

/* I2C3 Error  Interrupt */
#define SYS_INT_ID_I2C3_ER                               73u   

/* OTG HS EP1 OUT global Interrupt */
#define SYS_INT_ID_OTG_HS_EP1_OUT                        74u   

/* OTG HS EP1 IN global Interrupt */
#define SYS_INT_ID_OTG_HS_EP1_IN                         75u   

/* OTG HS Wakeup Interrupt */
#define SYS_INT_ID_OTG_HS_WKUP                           76u   

/* OTG HS global Interrupt */
#define SYS_INT_ID_OTG_HS                                77u   

/* DCMI global Interrupt */
#define SYS_INT_ID_DCMI                                  78u   

/* CRYPT crypto global Interrupt */
#define SYS_INT_ID_CRYP                                  79u   

/* HASH and RNG global Interrupt */
#define SYS_INT_ID_HASH_RNG                              80u   

/* FPU global Interrupt */
#define SYS_INT_ID_FPU                                   81u   

/* USART7 global Interrupt */
#define SYS_INT_ID_UART7                                 82u   

/* USART8 global Interrupt */
#define SYS_INT_ID_UART8                                 83u   

/* SPI4   global Interrupt */
#define SYS_INT_ID_SPI4                                  84u   

/* SPI6   global Interrupt */
#define SYS_INT_ID_SPI5                                  85u   

/* SPI7   global Interrupt */
#define SYS_INT_ID_SPI6                                  86u   

/* SAI1   Interrupt */
#define SYS_INT_ID_SAI1                                  87u   

/* LTDC   Interrupt */
#define SYS_INT_ID_LTDC                                  88u   

/* LTDC   Error Interrupt */
#define SYS_INT_ID_LTDC_ER                               89u   

/* DMA2D  Interrupt */
#define SYS_INT_ID_DMA2D                                 90u   

VOID  SYS_IntHandlerWWDG               (VOID) ;
VOID  SYS_IntHandlerPVD                (VOID) ;
VOID  SYS_IntHandlerTAMP_STAMP         (VOID) ;
VOID  SYS_IntHandlerRTC_WKUP           (VOID) ;
VOID  SYS_IntHandlerFLASH              (VOID) ;
VOID  SYS_IntHandlerRCC                (VOID) ;
VOID  SYS_IntHandlerEXTI0              (VOID) ;
VOID  SYS_IntHandlerEXTI1              (VOID) ;
VOID  SYS_IntHandlerEXTI2              (VOID) ;
VOID  SYS_IntHandlerEXTI3              (VOID) ;
VOID  SYS_IntHandlerEXTI4              (VOID) ;
VOID  SYS_IntHandlerDMA1_CH0           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH1           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH2           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH3           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH4           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH5           (VOID) ;
VOID  SYS_IntHandlerDMA1_CH6           (VOID) ;
VOID  SYS_IntHandlerADC                (VOID) ;
VOID  SYS_IntHandlerCAN1_TX            (VOID) ;
VOID  SYS_IntHandlerCAN1_RX0           (VOID) ;
VOID  SYS_IntHandlerCAN1_RX1           (VOID) ;
VOID  SYS_IntHandlerCAN1_SCE           (VOID) ;
VOID  SYS_IntHandlerEXTI9_5            (VOID) ;
VOID  SYS_IntHandlerTIM1_BRK_TIM9      (VOID) ;
VOID  SYS_IntHandlerTIM1_UP_TIM10      (VOID) ;
VOID  SYS_IntHandlerTIM1_TRG_COM_TIM11 (VOID) ;
VOID  SYS_IntHandlerTIM1_CC            (VOID) ;
VOID  SYS_IntHandlerTIM2               (VOID) ;
VOID  SYS_IntHandlerTIM3               (VOID) ;
VOID  SYS_IntHandlerTIM4               (VOID) ;
VOID  SYS_IntHandlerI2C1_EV            (VOID) ;
VOID  SYS_IntHandlerI2C1_ER            (VOID) ;
VOID  SYS_IntHandlerI2C2_EV            (VOID) ;
VOID  SYS_IntHandlerI2C2_ER            (VOID) ;
VOID  SYS_IntHandlerSPI1               (VOID) ;
VOID  SYS_IntHandlerSPI2               (VOID) ;
VOID  SYS_IntHandlerUSART1             (VOID) ;
VOID  SYS_IntHandlerUSART2             (VOID) ;
VOID  SYS_IntHandlerUSART3             (VOID) ;
VOID  SYS_IntHandlerEXTI15_10          (VOID) ;
VOID  SYS_IntHandlerRTCAlarm           (VOID) ;
VOID  SYS_IntHandlerOTG_FS_WKUP        (VOID) ;
VOID  SYS_IntHandlerTIM8_BRK_TIM12     (VOID) ;
VOID  SYS_IntHandlerTIM8_UP_TIM13      (VOID) ;
VOID  SYS_IntHandlerTIM8_TRG_COM_TIM14 (VOID) ;
VOID  SYS_IntHandlerTIM8_CC            (VOID) ;
VOID  SYS_IntHandlerDMA1_STREAM7       (VOID) ;
VOID  SYS_IntHandlerFSMC               (VOID) ;
VOID  SYS_IntHandlerSDIO               (VOID) ;
VOID  SYS_IntHandlerTIM5               (VOID) ;
VOID  SYS_IntHandlerSPI3               (VOID) ;
VOID  SYS_IntHandlerUSART4             (VOID) ;
VOID  SYS_IntHandlerUSART5             (VOID) ;
VOID  SYS_IntHandlerTIM6_DAC           (VOID) ;
VOID  SYS_IntHandlerTIM7               (VOID) ;
VOID  SYS_IntHandlerDMA2_CH0           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH1           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH2           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH3           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH4           (VOID) ;
VOID  SYS_IntHandlerETH                (VOID) ;
VOID  SYS_IntHandlerETHWakeup          (VOID) ;
VOID  SYS_IntHandlerCAN2_TX            (VOID) ;
VOID  SYS_IntHandlerCAN2_RX0           (VOID) ;
VOID  SYS_IntHandlerCAN2_RX1           (VOID) ;
VOID  SYS_IntHandlerCAN2_SCE           (VOID) ;
VOID  SYS_IntHandlerOTG_FS             (VOID) ;
VOID  SYS_IntHandlerDMA2_CH5           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH6           (VOID) ;
VOID  SYS_IntHandlerDMA2_CH7           (VOID) ;
VOID  SYS_IntHandlerUSART6             (VOID) ;
VOID  SYS_IntHandlerI2C3_EV            (VOID) ;
VOID  SYS_IntHandlerI2C3_ER            (VOID) ;
VOID  SYS_IntHandlerOTG_HS_EP1_OUT     (VOID) ;
VOID  SYS_IntHandlerOTG_HS_EP1_IN      (VOID) ;
VOID  SYS_IntHandlerOTG_HS_WKUP        (VOID) ;
VOID  SYS_IntHandlerOTG_HS             (VOID) ;
VOID  SYS_IntHandlerDCMI               (VOID) ;
VOID  SYS_IntHandlerCRYP               (VOID) ;
VOID  SYS_IntHandlerHASH_RNG           (VOID) ;
VOID  SYS_IntHandlerFPU                (VOID) ;
VOID  SYS_IntHandlerUART7              (VOID) ;
VOID  SYS_IntHandlerUART8              (VOID) ;
VOID  SYS_IntHandlerSPI4               (VOID) ;
VOID  SYS_IntHandlerSPI5               (VOID) ;
VOID  SYS_IntHandlerSPI6               (VOID) ;
VOID  SYS_IntHandlerSAI1               (VOID) ;
VOID  SYS_IntHandlerLTDC               (VOID) ;
VOID  SYS_IntHandlerLTDC_ER            (VOID) ;
VOID  SYS_IntHandlerDMA2D              (VOID) ;

static VOID __SYS_IntHandler (UINT uiInterruptId) ;
static VOID __SYS_IntHandlerDummy (VOID) ;

VOID __SYS_SystemInterruptInit(VOID) ;
VOID SYS_SystemInterruptEnable(UINT uiInterruptId) ;
VOID SYS_SystemInterruptDisable(UINT uiInterruptId) ;
void SYS_SystemInterruptPrioritySet(UINT uiInterruptId, UCHAR ucPriority) ;


#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif /* __SYS_INTERRUPT_H__ */

/******* End of file sys_interrupt.h. *******/  
