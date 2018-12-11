
#include "stdio.h"
#include "os.h"
#include "sys_arch.h"
#include "sys.h"
#include "string.h"

/*----------------------------------------------------------------------------*/
/*                      DEFINITIONS                                           */
/*----------------------------------------------------------------------------*/
#define LWIP_ARCH_TICK_PER_MS       (1000/OS_CFG_TICK_RATE_HZ)

/*----------------------------------------------------------------------------*/
/*                      VARIABLES                                             */
/*----------------------------------------------------------------------------*/
const void * const pvNullPointer = (mem_ptr_t*)0xffffffff;

CPU_STK       LwIP_Task_Stk[LWIP_TASK_MAX][LWIP_STK_SIZE];
OS_TCB        LwIP_Task_TCB[LWIP_TASK_MAX];
CPU_INT08U    LwIP_Task_Count = 0;

/*----------------------------------------------------------------------------*/
/*                      PROTOTYPES                                            */
/*----------------------------------------------------------------------------*/
static CPU_SR_ALLOC();
sys_prot_t sys_arch_protect(void)
{
	CPU_CRITICAL_ENTER();
	return 0;
}

void sys_arch_unprotect(sys_prot_t pval)
{
	LWIP_UNUSED_ARG(pval);
	CPU_CRITICAL_EXIT();
}

//===========================================================================================
// Function : 创建一个邮箱,这里用UCOS3的消息队列来实现
// *mbox    : 消息邮箱
// size     : 邮箱大小
// Return   : 创建成功返回ERR_OK, 创建失败返回ERR_MEM
//===========================================================================================
err_t sys_mbox_new(sys_mbox_t *mbox, int size)
{
    OS_ERR enErr ;
        
    OSQCreate(mbox, "LWIP QUEUE", size, &enErr) ;

    if(OS_ERR_NONE == enErr)
    {
        return ERR_OK ;
    }
    else
    {
        return ERR_MEM ;
    }
}
/*-----------------------------------------------------------------------------------*/
/*
  Deallocates a mailbox. If there are messages still present in the
  mailbox when the mailbox is deallocated, it is an indication of a
  programming error in lwIP and the developer should be notified.
*/
void sys_mbox_free(sys_mbox_t *mbox)
{
    OS_ERR enErr ;
    
	OSQFlush(mbox, &enErr);
    
	OSQDel(mbox, OS_OPT_DEL_ALWAYS, &enErr);

    return ;
}

void sys_mbox_post(sys_mbox_t *mbox, void *msg)
{
    OS_ERR enErr; 
	
    if (msg== NULL)
	{
		msg = (void *)&pvNullPointer;
	}

	while(1)
	{
		OSQPost(mbox, msg, 0, OS_OPT_POST_ALL, &enErr) ;
		if (enErr == OS_ERR_NONE)
		{
			break;
		}
		OSTimeDly(1, OS_OPT_TIME_DLY, &enErr) ;
	}
}

err_t sys_mbox_trypost(sys_mbox_t *mbox, void *msg)
{
    OS_ERR enErr;

    if (msg == NULL)
	{
		msg = (void *)&pvNullPointer;
	}
	
	OSQPost(mbox, msg, 0, OS_OPT_POST_ALL, &enErr) ;    
    
	if (enErr != OS_ERR_NONE)
	{
		return ERR_MEM ;
	}
	return ERR_OK ;
}

u32_t sys_arch_mbox_fetch(sys_mbox_t *mbox, void **msg, u32_t timeout)
{
    void        *temp;
    OS_ERR       enErr;
    OS_MSG_SIZE  msg_size;
    CPU_TS       TickBegin, TickEnd;  
  CPU_TS OSTimeout = timeout / LWIP_ARCH_TICK_PER_MS;
	
    if ((timeout != 0) && OSTimeout == 0)
    {
        OSTimeout = 1;
    }
    TickBegin = OSTimeGet(&enErr);
    temp = OSQPend(mbox, OSTimeout, OS_OPT_PEND_BLOCKING, &msg_size, NULL, &enErr);

    if (msg != NULL)
    {
		if (temp == (void*)&pvNullPointer)
            *msg = NULL;
        else
            *msg = temp;
    }
    if (enErr == OS_ERR_TIMEOUT)
    {
        return SYS_ARCH_TIMEOUT;
    }
    else
    {
        TickEnd = OSTimeGet(&enErr);
        if (TickEnd > TickBegin)
        {
			return ((TickEnd - TickBegin) * LWIP_ARCH_TICK_PER_MS + 1);
        }
        else
        {
			return ((0xffffffff - TickBegin + TickEnd) * LWIP_ARCH_TICK_PER_MS + 1);
        }
	}
}

u32_t sys_arch_mbox_tryfetch(sys_mbox_t *mbox, void **msg)
{
	if (sys_arch_mbox_fetch(mbox, msg, 1) == SYS_ARCH_TIMEOUT)
	{
		return SYS_MBOX_EMPTY;
	}
	else
	{
		return 0;
	}
}

int sys_mbox_valid(sys_mbox_t *mbox)
{
    if (mbox->NamePtr)  
    {
        return (strcmp(mbox->NamePtr,"?Q")) ? 1 : 0 ;
    }
    else
    {
        return 0 ;
    }
}

void sys_mbox_set_invalid(sys_mbox_t *mbox)
{
    if (sys_mbox_valid(mbox))
    {
        sys_mbox_free(mbox) ;
    }
}

err_t sys_sem_new(sys_sem_t *sem, u8_t count)
{
    OS_ERR enErr;
	
    OSSemCreate(sem, "LWIP Sem", count, &enErr);
    if (enErr != OS_ERR_NONE)
    {
        return -1;    
    }
    return 0;
}

u32_t sys_arch_sem_wait(sys_sem_t *sem, u32_t timeout)
{
  OS_ERR enErr;
  CPU_TS TickBegin, TickEnd; 
  CPU_TS OStimeout = timeout / LWIP_ARCH_TICK_PER_MS;
	
	if ((timeout != 0) && OStimeout == 0)
	{
		OStimeout = 1;
	}
	TickBegin = OSTimeGet(&enErr);
	OSSemPend(sem, OStimeout, OS_OPT_PEND_BLOCKING, NULL, &enErr);
	
  if (enErr == OS_ERR_TIMEOUT)
	{
		return SYS_ARCH_TIMEOUT;
	}
	else
	{
		TickEnd = OSTimeGet(&enErr);
		if (TickEnd > TickBegin)
			return ((TickEnd - TickBegin) * LWIP_ARCH_TICK_PER_MS + 1);
		else
			return ((0xffffffff - TickBegin + TickEnd) * LWIP_ARCH_TICK_PER_MS + 1);
	}
}

void sys_sem_signal(sys_sem_t *sem)
{
  OS_ERR enErr;
  
  OSSemPost(sem, OS_OPT_POST_ALL, &enErr);
}

void sys_sem_free(sys_sem_t *sem)
{
	OS_ERR enErr;
	
	OSSemDel(sem, OS_OPT_DEL_ALWAYS, &enErr);
}

int sys_sem_valid(sys_sem_t *sem)
{
	if (sem->NamePtr)
		return (strcmp(sem->NamePtr, "?SEM")) ? 1 : 0;
	else
		return 0;
}

void sys_sem_set_invalid(sys_sem_t *sem)
{
  if (sys_sem_valid(sem))
		sys_sem_free(sem);
}

void sys_init(void)
{
	LwIP_Task_Count = 0;
	memset(LwIP_Task_Stk, 0, sizeof(LwIP_Task_Stk));
	memset(LwIP_Task_TCB, 0, sizeof(LwIP_Task_TCB));
}

sys_thread_t sys_thread_new(const char *name, lwip_thread_fn thread, void *arg, int stacksize, int prio)
{
	OS_ERR err;
	
	CPU_SR_ALLOC();
	
	if (LwIP_Task_Count < LWIP_TASK_MAX)
	{
		CPU_CRITICAL_ENTER();
		
		OSTaskCreate((OS_TCB     *)&LwIP_Task_TCB[LwIP_Task_Count],
                 (CPU_CHAR   *) name,
                 (OS_TASK_PTR ) thread,
                 (void       *) arg,
                 (OS_PRIO     ) prio,
                 (CPU_STK    *) LwIP_Task_Stk[LwIP_Task_Count],
                 (CPU_STK_SIZE) LWIP_STK_SIZE / 10,
                 (CPU_STK_SIZE) LWIP_STK_SIZE,
                 (OS_MSG_QTY  ) 5u,
                 (OS_TICK     ) 0u,
                 (void       *) 0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
		
		CPU_CRITICAL_EXIT();
		
		if (err == OS_ERR_NONE)
		{
			LwIP_Task_Count ++;
		}
	}

	return err;
}








