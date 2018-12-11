/*******************************************************************************
 Copyright SAKC Corporation. 2016. All rights reserved.
--------------------------------------------------------------------------------
    File name    : sys_cfg.c
    Project name : 公共可移植模块。
    Module name  : 
    Date created : 2017年8月17日   10时19分43秒
    Author       : Ning.JianLi
    Description  : STM32系统配置接口。
*******************************************************************************/

#include "sys_cfg.h"

#ifdef __cplusplus
extern "c" {
#endif /* __cplusplus */

ETH_InitTypeDef g_stEthInitInfo ;
UINT            g_uiEthStatus ;
struct netif    g_stNetIf ;



/* 该函数的定义使得printf函数可以将信息输出在USART端口上 */
INT fputc(INT iChar, FILE *pstFile)
{
    USART_SendData(USART1, (UCHAR)iChar);
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    return iChar;
}

VOID Delay(UINT uiDelay)
{
    OS_ERR enErr ;
    
    OSTimeDly(uiDelay, OS_OPT_TIME_DLY, &enErr) ;
    return ;
}


VOID __SYS_SystemClockConfig(VOID)
{
    /* 初始化系统时钟 */
    RCC_DeInit() ;
    RCC_HSEConfig(RCC_HSE_ON) ;
    if(ERROR == RCC_WaitForHSEStartUp())
    {
        return ;
    }

    /* 锁相环各个系数设置 */
    RCC_PLLConfig(RCC_PLLSource_HSE, 
                  SYS_PLL_CONFIG_INFO_PLLM ,
                  SYS_PLL_CONFIG_INFO_PLLN ,
                  SYS_PLL_CONFIG_INFO_PLLP ,
                  SYS_PLL_CONFIG_INFO_PLLQ) ;

    /* AHB时钟和SYSCLK一致 */
    RCC_HCLKConfig(RCC_SYSCLK_Div1) ;

    /* APB1总线时钟工作在AHB总线时钟的1/4 */
    RCC_PCLK1Config(RCC_HCLK_Div4) ;

    /* APB1总线时钟工作在AHB总线时钟的1/2 */
    RCC_PCLK2Config(RCC_HCLK_Div2) ;

    /* 启动锁相环 */
    RCC_PLLCmd(ENABLE) ;

    /* 等待锁相环锁定 */
    while(RESET == RCC_GetFlagStatus(RCC_FLAG_PLLRDY)) ;

    /* 对于运行在168MHz的STM32F4，FLASH等待周期应设置为5 */
    FLASH_SetLatency(FLASH_Latency_5) ;

    /* 允许预取 */
    FLASH_PrefetchBufferCmd(ENABLE) ;

    /* 允许指令Cache */
    FLASH_InstructionCacheCmd(ENABLE) ;

    /* 允许数据Cache */
    FLASH_DataCacheCmd(ENABLE) ;

    /* 选择PLL输出作为系统时钟 */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK) ;

    /* 等待系统时钟切换完成 */
    while(0x08 != RCC_GetSYSCLKSource()) ;

    return ;
}

VOID __SYS_SystemAllGPIOConfig(VOID)
{
    GPIO_InitTypeDef stGPIOInitInfo ;

    /* LED GPIO配置 */
    /* LED使用GPIOH组的10、11、12引脚 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE) ;
    
    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 ;
    stGPIOInitInfo.GPIO_Mode  = GPIO_Mode_OUT ;
    stGPIOInitInfo.GPIO_Speed = GPIO_Speed_50MHz ;
    stGPIOInitInfo.GPIO_OType = GPIO_OType_PP ;
    stGPIOInitInfo.GPIO_PuPd  = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOH, &stGPIOInitInfo) ;

    /* 熄灭所有的LED灯 */
    GPIO_SetBits(GPIOH, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12) ;
    
    /* 系统串口CPIO配置 */
    /* 系统串口使用GPIOA组的9、10引脚 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE) ;

    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_9 | GPIO_Pin_10 ;
    stGPIOInitInfo.GPIO_Mode  = GPIO_Mode_AF ;
    stGPIOInitInfo.GPIO_Speed = GPIO_Speed_50MHz ;
    stGPIOInitInfo.GPIO_OType = GPIO_OType_PP ;
    stGPIOInitInfo.GPIO_PuPd  = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &stGPIOInitInfo) ;

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1) ;
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1) ;

    /* 以太网端口使用的GPIO的配置 */
    /* -----------------------------------
     * | FUNC PIN NAME    | PIN LOCATION |
     * -----------------------------------
     * | ETH_MDIO         | PA2          |
     * | ETH_MDC          | PC1          |
     * | ETH_RMII_REF_CLK | PA1          |
     * | ETH_RMII_CRS_DV  | PA7          |
     * | ETH_RMII_RXD0    | PC4          |
     * | ETH_RMII_RXD1    | PC5          |
     * | ETH_RMII_TX_EN   | PB11         |
     * | ETH_RMII_TXD0    | PG13         |
     * | ETH_RMII_TXD1    | PG14         |
     * | ETH_NRST         | PI1          |
     * -----------------------------------
     */

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE) ;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE) ;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE) ;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE) ;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE) ;

    stGPIOInitInfo.GPIO_Mode  = GPIO_Mode_AF ;
    stGPIOInitInfo.GPIO_Speed = GPIO_Speed_100MHz ;
    stGPIOInitInfo.GPIO_OType = GPIO_OType_PP ;
    stGPIOInitInfo.GPIO_PuPd  = GPIO_PuPd_NOPULL ;
    
    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_7 ;
    GPIO_Init(GPIOA, &stGPIOInitInfo) ;

    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_11 ;
    GPIO_Init(GPIOB, &stGPIOInitInfo) ;

    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 ;
    GPIO_Init(GPIOC, &stGPIOInitInfo) ;

    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_13 | GPIO_Pin_14 ;
    GPIO_Init(GPIOG, &stGPIOInitInfo) ;

    stGPIOInitInfo.GPIO_Pin   = GPIO_Pin_1 ;
    stGPIOInitInfo.GPIO_Mode  = GPIO_Mode_OUT ;
    GPIO_Init(GPIOI, &stGPIOInitInfo) ;

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_ETH) ;
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_ETH) ;
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_ETH) ;

    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_ETH) ;
    
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource1, GPIO_AF_ETH) ;
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource4, GPIO_AF_ETH) ;
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource5, GPIO_AF_ETH) ;

    GPIO_PinAFConfig(GPIOG, GPIO_PinSource13, GPIO_AF_ETH) ;
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_ETH) ;

    //GPIO_PinAFConfig(GPIOI, GPIO_PinSource1, GPIO_AF_ETH) ;

    return ;
}

VOID __SYS_SystemEthPortTypeConfig(VOID)
{
    /* 使能SYSCFG单元的时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE) ;

    /* 使能RMII接口模式 */
    SYSCFG_ETH_MediaInterfaceConfig(SYSCFG_ETH_MediaInterface_RMII) ;

    return ;
}

VOID __SYS_SystemEthNVICConfig(VOID)
{
    NVIC_InitTypeDef   stNVICInitInfo ; 
    
    /* 使能以太网端口全局中断 */
    stNVICInitInfo.NVIC_IRQChannel                   = ETH_IRQn;
    stNVICInitInfo.NVIC_IRQChannelPreemptionPriority = 12 ;
    stNVICInitInfo.NVIC_IRQChannelSubPriority        = 0;
    stNVICInitInfo.NVIC_IRQChannelCmd                = ENABLE;
    NVIC_Init(&stNVICInitInfo);
}

VOID __SYS_SystemEthMACDMAConfig(VOID)
{
    /* 使能以太网MAC时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_ETH_MAC | 
                           RCC_AHB1Periph_ETH_MAC_Tx | 
                           RCC_AHB1Periph_ETH_MAC_Rx, 
                           ENABLE);

    /* 复位以太网MAC */
    ETH_DeInit() ;

    /* 复位以太网DMA引擎 */
    ETH_SoftwareReset() ;
    while (ETH_GetSoftwareResetStatus() == SET);

    /* MAC初始化 */
    ETH_StructInit(&g_stEthInitInfo) ;
    
    g_stEthInitInfo.ETH_AutoNegotiation             = ETH_AutoNegotiation_Enable ; 
                                                    
    g_stEthInitInfo.ETH_LoopbackMode                = ETH_LoopbackMode_Disable ;
    g_stEthInitInfo.ETH_RetryTransmission           = ETH_RetryTransmission_Disable ;
    g_stEthInitInfo.ETH_AutomaticPadCRCStrip        = ETH_AutomaticPadCRCStrip_Disable ;
    g_stEthInitInfo.ETH_ReceiveAll                  = ETH_ReceiveAll_Disable ;
    g_stEthInitInfo.ETH_BroadcastFramesReception    = ETH_BroadcastFramesReception_Enable ;
    g_stEthInitInfo.ETH_PromiscuousMode             = ETH_PromiscuousMode_Disable ;
    g_stEthInitInfo.ETH_MulticastFramesFilter       = ETH_MulticastFramesFilter_Perfect ;
    g_stEthInitInfo.ETH_UnicastFramesFilter         = ETH_UnicastFramesFilter_Perfect ;
                                                    
    g_stEthInitInfo.ETH_ChecksumOffload             = ETH_ChecksumOffload_Enable ;
                                                    
    g_stEthInitInfo.ETH_DropTCPIPChecksumErrorFrame = ETH_DropTCPIPChecksumErrorFrame_Enable ;
    g_stEthInitInfo.ETH_ReceiveStoreForward         = ETH_ReceiveStoreForward_Enable ;
    g_stEthInitInfo.ETH_TransmitStoreForward        = ETH_TransmitStoreForward_Enable ;
                                                    
    g_stEthInitInfo.ETH_ForwardErrorFrames          = ETH_ForwardErrorFrames_Disable ;
    g_stEthInitInfo.ETH_ForwardUndersizedGoodFrames = ETH_ForwardUndersizedGoodFrames_Disable ;
    g_stEthInitInfo.ETH_SecondFrameOperate          = ETH_SecondFrameOperate_Enable ;
    g_stEthInitInfo.ETH_AddressAlignedBeats         = ETH_AddressAlignedBeats_Enable ;
    g_stEthInitInfo.ETH_FixedBurst                  = ETH_FixedBurst_Enable ;
    g_stEthInitInfo.ETH_RxDMABurstLength            = ETH_RxDMABurstLength_32Beat ;
    g_stEthInitInfo.ETH_TxDMABurstLength            = ETH_TxDMABurstLength_32Beat ;
    g_stEthInitInfo.ETH_DMAArbitration              = ETH_DMAArbitration_RoundRobin_RxTx_1_1 ;
    
    /* 配置以太网 */
    g_uiEthStatus = ETH_Init(&g_stEthInitInfo, (USHORT)SYS_ETH_PHY_ADDRESS) ;
    
    /* 允许接收中段 */
    //ETH_DMAITConfig(ETH_DMA_IT_NIS | ETH_DMA_IT_R, ENABLE);

    return ;
}

VOID __SYS_SystemEthPhyReset(VOID)
{
    unsigned int uiDelay ;
    /* 拉低引脚进行PHY复位 */
    GPIO_ResetBits(GPIOI, GPIO_Pin_1) ;
    uiDelay = 0xfffff ;
    while(uiDelay--) ;

    /* 拉高引脚撤销PHY复位 */
    GPIO_SetBits(GPIOI, GPIO_Pin_1) ;
    uiDelay = 0xfffff ;
    while(uiDelay--) ;

    return ;
}

VOID __SYS_SystemEthConfig(VOID)
{
    /* 配置系统以太网MAC使用RMII接口 */
    __SYS_SystemEthPortTypeConfig() ;

    /* 复位PHY */
    __SYS_SystemEthPhyReset() ;
    
    /* 使能以太网中断 */
    //__SYS_SystemEthNVICConfig() ;
    //SYS_SystemInterruptEnable(SYS_INT_ID_ETH) ;

    /* 以太网MAC及DMA引擎配置 */
    __SYS_SystemEthMACDMAConfig() ;

    /* 获取当前PHY的连接状态(UP/DOWN) */
    if(PHY_Linked_Status == ETH_ReadPHYRegister(SYS_ETH_PHY_ADDRESS, PHY_BSR) & PHY_Linked_Status)
    {
        /* 链路OK */
        g_uiEthStatus |= SYS_ETH_LINK_FLAG ;
    }
    /* TODO: 此处可添加Link UP/DOWN 时的中断处理代码，但需要外部PHY支持中断。
     *       LAN8720和DP83848都支持该功能，但开发板上硬件不能支持。
     */

    return ;
}

VOID __SYS_SystemSerialPortConfig(VOID)
{
    USART_InitTypeDef stUSARTInitInfo ;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE) ;

    /* 115200-8-1-N-N */
    stUSARTInitInfo.USART_BaudRate            = 115200 ;
    stUSARTInitInfo.USART_WordLength          = USART_WordLength_8b ;
    stUSARTInitInfo.USART_StopBits            = USART_StopBits_1 ;
    stUSARTInitInfo.USART_Parity              = USART_Parity_No ;
    stUSARTInitInfo.USART_Mode                = USART_Mode_Rx | USART_Mode_Tx ;
    stUSARTInitInfo.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;

    USART_Init(USART1, &stUSARTInitInfo) ;
    USART_Cmd(USART1, ENABLE) ;
}


VOID SYS_SystemConfig(VOID)
{
    /* 系统时钟配置 */
    __SYS_SystemClockConfig() ;

    /* GPIO配置 */
    __SYS_SystemAllGPIOConfig() ;

    /* 系统串口配置 */ 
    __SYS_SystemSerialPortConfig() ;
    
    /* 以太网接口配置 */
    __SYS_SystemEthConfig() ;

    /* 中断处理函数表初始化 */
    __SYS_SystemInterruptInit() ;

    return ;
}

VOID __SYS_SystemEthLinkCallback(struct netif *pstNetIF)
{
    UINT   uiTimeOut = 0 ;
    UINT   uiTmpReg ;
    UINT   uiRegVal ;
    struct ip_addr stIPAddr ;
    struct ip_addr stNetMask ;
    struct ip_addr stGateWay ;

    if(netif_is_link_up(pstNetIF))
    {
        /* 重新进行自动协商 */
        if(g_stEthInitInfo.ETH_AutoNegotiation != ETH_AutoNegotiation_Disable)
        {
            /* 重置超时计数器 */
            uiTimeOut = 0;

            /* 允许自动协商 */
            ETH_WritePHYRegister(0, PHY_BCR, PHY_AutoNegotiation);

            /* 等待，直到自动协商完成 */
            do
            {
                uiTimeOut++;
            } while (!(ETH_ReadPHYRegister(0, PHY_BSR) & PHY_AutoNego_Complete) && (uiTimeOut < (UINT)PHY_READ_TO));

            /* 重置超时定时器 */
            uiTimeOut = 0;

            /* 读取自动协商结果 */
            uiRegVal = ETH_ReadPHYRegister(0, PHY_SR);
    
            /* 根据协商结果来配置MAC的双工模式 */
            if((uiRegVal & PHY_DUPLEX_STATUS) != (UINT)RESET)
            {
                /* 全双工模式 */
                g_stEthInitInfo.ETH_Mode = ETH_Mode_FullDuplex;  
            }
            else
            {
                /* 半双工模式 */
                g_stEthInitInfo.ETH_Mode = ETH_Mode_HalfDuplex;
            }
            
            /* 根据协商结果来配置链路速度 */
            if(uiRegVal & PHY_SPEED_STATUS)
            {
                /* 10Mbps */
                g_stEthInitInfo.ETH_Speed = ETH_Speed_10M; 
            }
            else
            {
                /* 100Mbps */
                g_stEthInitInfo.ETH_Speed = ETH_Speed_100M;      
            }

            /* 以太网MAC CR寄存器重新配置 */
            /* 获取当前CR值 */  
            uiTmpReg = ETH->MACCR;

            /* 根据速度设置FES位 */ 
            /* 根据模式设置DM位 */ 
            uiTmpReg |= (UINT)(g_stEthInitInfo.ETH_Speed | g_stEthInitInfo.ETH_Mode);

            /* 写入至MAC CR寄存器 */
            ETH->MACCR = (UINT)uiTmpReg;

            _eth_delay_(ETH_REG_WRITE_DELAY);
            uiTmpReg = ETH->MACCR;
            ETH->MACCR = uiTmpReg;
        }

        /* 重启MAC接口 */
        ETH_Start();

        /* 设置网卡参数 */
        IP4_ADDR(&stIPAddr, 
                  SYS_ETH_IP_ADDR0, 
                  SYS_ETH_IP_ADDR1, 
                  SYS_ETH_IP_ADDR2, 
                  SYS_ETH_IP_ADDR3) ;
    
        IP4_ADDR(&stNetMask, 
                  SYS_ETH_NET_MASK0, 
                  SYS_ETH_NET_MASK1, 
                  SYS_ETH_NET_MASK2, 
                  SYS_ETH_NET_MASK3) ;
    
        IP4_ADDR(&stGateWay, 
                  SYS_ETH_GATE_WAY0, 
                  SYS_ETH_GATE_WAY1, 
                  SYS_ETH_GATE_WAY2, 
                  SYS_ETH_GATE_WAY3) ;


        netif_set_addr(&g_stNetIf, 
                       &stIPAddr, 
                       &stNetMask, 
                       &stGateWay) ;
    
        /* 使得接口UP */
        netif_set_up(&g_stNetIf);    
    }
    else
    {
        ETH_Stop();

        /* 断开链路，设置接口DOWN */
        netif_set_down(&g_stNetIf);
    }
}

VOID SYS_LWIPInit(VOID)
{
    struct ip_addr stIPAddr ;
    struct ip_addr stNetMask ;
    struct ip_addr stGateWay ;

    /* 创建TCP/IP协议栈线程 */
    tcpip_init( NULL, NULL );	

    /* 设置网卡参数 */
    IP4_ADDR(&stIPAddr, 
              SYS_ETH_IP_ADDR0, 
              SYS_ETH_IP_ADDR1, 
              SYS_ETH_IP_ADDR2, 
              SYS_ETH_IP_ADDR3) ;
    
    IP4_ADDR(&stNetMask, 
              SYS_ETH_NET_MASK0, 
              SYS_ETH_NET_MASK1, 
              SYS_ETH_NET_MASK2, 
              SYS_ETH_NET_MASK3) ;
    
    IP4_ADDR(&stGateWay, 
              SYS_ETH_GATE_WAY0, 
              SYS_ETH_GATE_WAY1, 
              SYS_ETH_GATE_WAY2, 
              SYS_ETH_GATE_WAY3) ;

    /* 添加网卡 */
    netif_add(&g_stNetIf, 
              &stIPAddr, 
              &stNetMask, 
              &stGateWay, 
              NULL, 
              &ethernetif_init, 
              &tcpip_input);

    /* 注册初始网卡 */
    netif_set_default(&g_stNetIf);

    //if (g_uiEthStatus == (SYS_ETH_INIT_FLAG | SYS_ETH_LINK_FLAG))
    //{ 
        /* 设置链路UP标记 */
        g_stNetIf.flags |= NETIF_FLAG_LINK_UP;

        /* 配置完成后必须调用本函数 */
        netif_set_up(&g_stNetIf);
    //}
    //else
    //{
        /* 如果链路DOWN则设置接口DOWN */
        //netif_set_down(&g_stNetIf);
    //}

    /* 链路状态发生变化时的回调函数 */
    //netif_set_link_callback(&g_stNetIf, __SYS_SystemEthLinkCallback);
}

VOID SYS_SystemTickInit(VOID)
{
    RCC_ClocksTypeDef stRCCClockFreqInfo ;
    UINT              uiCnts ;

    /* 获取系统时钟频率 */
    RCC_GetClocksFreq(&stRCCClockFreqInfo) ;

    uiCnts = stRCCClockFreqInfo.HCLK_Frequency / OSCfg_TickRate_Hz ;

    /* 以计算出的systick运行重装载值来初始化systick */
    OS_CPU_SysTickInit(uiCnts) ;

    return ;
}

#if (CPU_CFG_TS_TMR_EN == DEF_ENABLED)
VOID  CPU_TS_TmrInit(VOID)
{
    RCC_ClocksTypeDef stRCCClockFreqInfo ;
    
    /* 获取系统时钟频率 */
    RCC_GetClocksFreq(&stRCCClockFreqInfo) ;

    SYS_REG_DEM_CR     |= (CPU_INT32U)SYS_BIT_DEM_CR_TRCENA;    /* Enable Cortex-M4's DWT CYCCNT reg.                   */
    SYS_REG_DWT_CYCCNT  = (CPU_INT32U)0u;
    SYS_REG_DWT_CR     |= (CPU_INT32U)SYS_BIT_DWT_CR_CYCCNTENA;
    
    CPU_TS_TmrFreqSet(stRCCClockFreqInfo.HCLK_Frequency) ;

    return ;
}

CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    CPU_TS_TMR  ts_tmr_cnts;

    ts_tmr_cnts = (CPU_TS_TMR)SYS_REG_DWT_CYCCNT;

    return (ts_tmr_cnts);
}

CPU_INT64U  CPU_TS32_to_uSec (CPU_TS32  ts_cnts)
{
    RCC_ClocksTypeDef stRCCClockFreqInfo ;

    RCC_GetClocksFreq(&stRCCClockFreqInfo) ;

    return(ts_cnts / (stRCCClockFreqInfo.HCLK_Frequency / DEF_TIME_NBR_uS_PER_SEC)) ;
}

CPU_INT64U  CPU_TS64_to_uSec (CPU_TS64  ts_cnts)
{
    RCC_ClocksTypeDef stRCCClockFreqInfo ;

    RCC_GetClocksFreq(&stRCCClockFreqInfo) ;

    return(ts_cnts / (stRCCClockFreqInfo.HCLK_Frequency / DEF_TIME_NBR_uS_PER_SEC)) ;
}

#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */
/******* End of file sys_cfg.c. *******/  
