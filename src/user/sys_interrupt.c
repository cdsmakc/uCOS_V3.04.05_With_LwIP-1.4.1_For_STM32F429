/*******************************************************************************
 Copyright SAKC Corporation. 2016. All rights reserved.
--------------------------------------------------------------------------------
    File name    : sys_interrupt.c
    Project name : 公共可移植模块。
    Module name  : 
    Date created : 2017年8月17日   14时30分31秒
    Author       : Ning.JianLi
    Description  : STM32移植UCOS操作系统的中断处理部分。
*******************************************************************************/

#include "sys_interrupt.h"

#ifdef __cplusplus
extern "c" {
#endif /* __cplusplus */

extern struct netif g_stNetIf ;

CPU_FNCT_VOID apInterruptCallbackTable[SYS_INTERRUPT_TOTAL_NUM] ;

/* 定义所有的中断处理函数 */
VOID  SYS_IntHandlerWWDG               (VOID)  { __SYS_IntHandler(SYS_INT_ID_WWDG);                }
VOID  SYS_IntHandlerPVD                (VOID)  { __SYS_IntHandler(SYS_INT_ID_PVD);                 }
VOID  SYS_IntHandlerTAMP_STAMP         (VOID)  { __SYS_IntHandler(SYS_INT_ID_TAMP_STAMP);          }
VOID  SYS_IntHandlerRTC_WKUP           (VOID)  { __SYS_IntHandler(SYS_INT_ID_RTC_WKUP);            }
VOID  SYS_IntHandlerFLASH              (VOID)  { __SYS_IntHandler(SYS_INT_ID_FLASH);               }
VOID  SYS_IntHandlerRCC                (VOID)  { __SYS_IntHandler(SYS_INT_ID_RCC);                 }
VOID  SYS_IntHandlerEXTI0              (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI0);               }
VOID  SYS_IntHandlerEXTI1              (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI1);               }
VOID  SYS_IntHandlerEXTI2              (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI2);               }
VOID  SYS_IntHandlerEXTI3              (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI3);               }
VOID  SYS_IntHandlerEXTI4              (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI4);               }
VOID  SYS_IntHandlerDMA1_CH0           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH0);            }
VOID  SYS_IntHandlerDMA1_CH1           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH1);            }
VOID  SYS_IntHandlerDMA1_CH2           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH2);            }
VOID  SYS_IntHandlerDMA1_CH3           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH3);            }
VOID  SYS_IntHandlerDMA1_CH4           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH4);            }
VOID  SYS_IntHandlerDMA1_CH5           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH5);            }
VOID  SYS_IntHandlerDMA1_CH6           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_CH6);            }
VOID  SYS_IntHandlerADC                (VOID)  { __SYS_IntHandler(SYS_INT_ID_ADC);                 }
VOID  SYS_IntHandlerCAN1_TX            (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN1_TX);             }
VOID  SYS_IntHandlerCAN1_RX0           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN1_RX0);            }
VOID  SYS_IntHandlerCAN1_RX1           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN1_RX1);            }
VOID  SYS_IntHandlerCAN1_SCE           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN1_SCE);            }
VOID  SYS_IntHandlerEXTI9_5            (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI9_5);             }
VOID  SYS_IntHandlerTIM1_BRK_TIM9      (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM1_BRK_TIM9);       }
VOID  SYS_IntHandlerTIM1_UP_TIM10      (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM1_UP_TIM10);       }
VOID  SYS_IntHandlerTIM1_TRG_COM_TIM11 (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM1_TRG_COM_TIM11);  }
VOID  SYS_IntHandlerTIM1_CC            (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM1_CC);             }
VOID  SYS_IntHandlerTIM2               (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM2);                }
VOID  SYS_IntHandlerTIM3               (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM3);                }
VOID  SYS_IntHandlerTIM4               (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM4);                }
VOID  SYS_IntHandlerI2C1_EV            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C1_EV);             }
VOID  SYS_IntHandlerI2C1_ER            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C1_ER);             }
VOID  SYS_IntHandlerI2C2_EV            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C2_EV);             }
VOID  SYS_IntHandlerI2C2_ER            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C2_ER);             }
VOID  SYS_IntHandlerSPI1               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI1);                }
VOID  SYS_IntHandlerSPI2               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI2);                }
VOID  SYS_IntHandlerUSART1             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART1);              }
VOID  SYS_IntHandlerUSART2             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART2);              }
VOID  SYS_IntHandlerUSART3             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART3);              }
VOID  SYS_IntHandlerEXTI15_10          (VOID)  { __SYS_IntHandler(SYS_INT_ID_EXTI15_10);           }
VOID  SYS_IntHandlerRTCAlarm           (VOID)  { __SYS_IntHandler(SYS_INT_ID_RTC_ALARM);           }
VOID  SYS_IntHandlerOTG_FS_WKUP        (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_FS_WKUP);         }
VOID  SYS_IntHandlerTIM8_BRK_TIM12     (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM8_BRK_TIM12);      }
VOID  SYS_IntHandlerTIM8_UP_TIM13      (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM8_UP_TIM13);       }
VOID  SYS_IntHandlerTIM8_TRG_COM_TIM14 (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM8_TRG_COM_TIM14);  }
VOID  SYS_IntHandlerTIM8_CC            (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM8_CC);             }
VOID  SYS_IntHandlerDMA1_STREAM7       (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA1_STREAM7);        }
VOID  SYS_IntHandlerFSMC               (VOID)  { __SYS_IntHandler(SYS_INT_ID_FSMC);                }
VOID  SYS_IntHandlerSDIO               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SDIO);                }
VOID  SYS_IntHandlerTIM5               (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM5);                }
VOID  SYS_IntHandlerSPI3               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI3);                }
VOID  SYS_IntHandlerUSART4             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART4);              }
VOID  SYS_IntHandlerUSART5             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART5);              }
VOID  SYS_IntHandlerTIM6_DAC           (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM6_DAC);            }
VOID  SYS_IntHandlerTIM7               (VOID)  { __SYS_IntHandler(SYS_INT_ID_TIM7);                }
VOID  SYS_IntHandlerDMA2_CH0           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH0);            }
VOID  SYS_IntHandlerDMA2_CH1           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH1);            }
VOID  SYS_IntHandlerDMA2_CH2           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH2);            }
VOID  SYS_IntHandlerDMA2_CH3           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH3);            }
VOID  SYS_IntHandlerDMA2_CH4           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH4);            }
VOID  SYS_IntHandlerETH                (VOID)  { __SYS_IntHandler(SYS_INT_ID_ETH);                 }
VOID  SYS_IntHandlerETHWakeup          (VOID)  { __SYS_IntHandler(SYS_INT_ID_ETH_WKUP);            }
VOID  SYS_IntHandlerCAN2_TX            (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN2_TX);             }
VOID  SYS_IntHandlerCAN2_RX0           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN2_RX0);            }
VOID  SYS_IntHandlerCAN2_RX1           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN2_RX1);            }
VOID  SYS_IntHandlerCAN2_SCE           (VOID)  { __SYS_IntHandler(SYS_INT_ID_CAN2_SCE);            }
VOID  SYS_IntHandlerOTG_FS             (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_FS);              }
VOID  SYS_IntHandlerDMA2_CH5           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH5);            }
VOID  SYS_IntHandlerDMA2_CH6           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH6);            }
VOID  SYS_IntHandlerDMA2_CH7           (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2_CH7);            }
VOID  SYS_IntHandlerUSART6             (VOID)  { __SYS_IntHandler(SYS_INT_ID_USART6);              }
VOID  SYS_IntHandlerI2C3_EV            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C3_EV);             }
VOID  SYS_IntHandlerI2C3_ER            (VOID)  { __SYS_IntHandler(SYS_INT_ID_I2C3_ER);             }
VOID  SYS_IntHandlerOTG_HS_EP1_OUT     (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_HS_EP1_OUT);      }
VOID  SYS_IntHandlerOTG_HS_EP1_IN      (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_HS_EP1_IN);       }
VOID  SYS_IntHandlerOTG_HS_WKUP        (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_HS_WKUP);         }
VOID  SYS_IntHandlerOTG_HS             (VOID)  { __SYS_IntHandler(SYS_INT_ID_OTG_HS);              }
VOID  SYS_IntHandlerDCMI               (VOID)  { __SYS_IntHandler(SYS_INT_ID_DCMI);                }
VOID  SYS_IntHandlerCRYP               (VOID)  { __SYS_IntHandler(SYS_INT_ID_CRYP);                }
VOID  SYS_IntHandlerHASH_RNG           (VOID)  { __SYS_IntHandler(SYS_INT_ID_HASH_RNG);            }
VOID  SYS_IntHandlerFPU                (VOID)  { __SYS_IntHandler(SYS_INT_ID_FPU);                 }
VOID  SYS_IntHandlerUART7              (VOID)  { __SYS_IntHandler(SYS_INT_ID_UART7);               }
VOID  SYS_IntHandlerUART8              (VOID)  { __SYS_IntHandler(SYS_INT_ID_UART8);               }
VOID  SYS_IntHandlerSPI4               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI4);                }
VOID  SYS_IntHandlerSPI5               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI5);                }
VOID  SYS_IntHandlerSPI6               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SPI6);                }
VOID  SYS_IntHandlerSAI1               (VOID)  { __SYS_IntHandler(SYS_INT_ID_SAI1);                }
VOID  SYS_IntHandlerLTDC               (VOID)  { __SYS_IntHandler(SYS_INT_ID_LTDC);                }
VOID  SYS_IntHandlerLTDC_ER            (VOID)  { __SYS_IntHandler(SYS_INT_ID_LTDC_ER);             }
VOID  SYS_IntHandlerDMA2D              (VOID)  { __SYS_IntHandler(SYS_INT_ID_DMA2D);               }

static  VOID  __SYS_IntHandler (UINT uiInterruptId)
{
    CPU_FNCT_VOID pInterruptHandler ;
    
    CPU_SR_ALLOC() ;
    
    CPU_CRITICAL_ENTER() ;
    /* Tell the OS that we are starting an ISR */
    OSIntEnter() ;

    CPU_CRITICAL_EXIT() ;

    if (uiInterruptId < SYS_INTERRUPT_TOTAL_NUM) 
    {
        pInterruptHandler = apInterruptCallbackTable[uiInterruptId];
        
        if (NULL != pInterruptHandler)
        {
            pInterruptHandler() ;
        }
    }

    /* Tell the OS that we are leaving the ISR */
    OSIntExit() ;

    return ;
}

/* 以太网中断处理函数 */
static VOID __SYS_IntHandlerCBEth(VOID)
{
    /* 检查是否有包被接收到 */
    if(1 == ETH_CheckFrameReceived())
    {
        ethernetif_input(&g_stNetIf);
    }

    if((ETH->DMASR & ETH_DMASR_RBUS) != (u32)RESET)
    { 
        ETH->DMASR = ETH_DMASR_RBUS;//重置ETH DMA RBUS位 
        ETH->DMARPDR = 0;//恢复DMA接收
    }
    ETH_DMAClearITPendingBit(ETH_DMA_IT_NIS | ETH_DMA_IT_AIS | ETH_DMA_IT_R);
}


VOID __SYS_SystemInterruptInit(VOID)
{
    UINT uiLoop ;
    CPU_SR_ALLOC() ;

    for(uiLoop = 0 ; SYS_INTERRUPT_TOTAL_NUM > uiLoop ; uiLoop++)
    {
        CPU_CRITICAL_ENTER();
        if(SYS_INT_ID_ETH == uiLoop) apInterruptCallbackTable[uiLoop] = __SYS_IntHandlerCBEth ; else
            apInterruptCallbackTable[uiLoop] = __SYS_IntHandlerDummy ;
        
        CPU_CRITICAL_EXIT();
    }
}

/* 中断处理函数模板 */
static VOID __SYS_IntHandlerDummy (VOID)
{

}

VOID SYS_SystemInterruptEnable(UINT uiInterruptId)
{
    if (SYS_INTERRUPT_TOTAL_NUM > uiInterruptId) 
    {
        /* +16使得包含系统中断 */
        CPU_IntSrcEn(uiInterruptId + 16);
    }
}

VOID SYS_SystemInterruptDisable(UINT uiInterruptId)
{
    if (SYS_INTERRUPT_TOTAL_NUM > uiInterruptId)
    {
        /* +16使得包含系统中断 */
        CPU_IntSrcDis(uiInterruptId + 16);
    }
}

void SYS_SystemInterruptPrioritySet(UINT uiInterruptId, UCHAR ucPriority)
{
    CPU_SR_ALLOC();

    if (SYS_INTERRUPT_TOTAL_NUM > uiInterruptId)
    {
        CPU_CRITICAL_ENTER();
        /* +16使得包含系统中断 */
        CPU_IntSrcPrioSet(uiInterruptId + 16, ucPriority);
        CPU_CRITICAL_EXIT();
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
/******* End of file sys_interrupt.c. *******/  
