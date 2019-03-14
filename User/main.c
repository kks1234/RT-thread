#include <rtthread.h>
#include <rthw.h>
#include <ARMCM3.h>


/* �߳̾����б� */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

/* ����ȫ�ֱ��� */
rt_uint8_t flag1;
rt_uint8_t flag2;
rt_uint8_t flag3;


/* �����߳̿��ƿ� */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;
struct rt_thread rt_flag3_thread;


ALIGN(RT_ALIGN_SIZE)



/* �����߳�ջ */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];
rt_uint8_t rt_flag3_thread_stack[512];




/* �̺߳������� */
void flag1_thread_entry(void* p_arg);
void flag2_thread_entry(void* p_arg);
void flag3_thread_entry(void* p_arg);
/* �����ʱ�������� */
void delay(rt_uint32_t count);






int  main()
{
	/* Ӳ����ʼ�� */
	/* ��Ӳ����س�ʼ�������� �����������û����س�ʼ������ */
	
	
	
	
	
	/* ���ж� */
	rt_hw_interrupt_disable();
	
	/* SysTick �ж�Ƶ������ */
	SysTick_Config(SystemCoreClock / RT_TICK_PER_SECOND);
	
	/* ϵͳ��ʱ���б��ʼ�� */
	rt_system_timer_init();
	
	/* ��������ʼ�� */
	rt_system_scheduler_init();
	
	/* ��ʼ�������߳� */
	rt_thread_idle_init();
	
	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag1_thread,
					"rt_flag1_thread",
					flag1_thread_entry,
					RT_NULL,
					&rt_flag1_thread_stack[0],
					sizeof(rt_flag1_thread_stack),
					2);
	/* ���̲߳��뵽�����б� */
//	rt_list_insert_before(&(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist));
	rt_thread_startup(&rt_flag1_thread);
					
					
	
	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag2_thread,
					"rt_flag2_thread",
					flag2_thread_entry,
					RT_NULL,
					&rt_flag2_thread_stack[0],
					sizeof(rt_flag2_thread_stack),
					3);	
	/* ���̲߳��뵽�����б� */
//	rt_list_insert_before(&(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist));
	rt_thread_startup(&rt_flag2_thread);
					
	
	/* ��ʼ���߳� */
	rt_thread_init(&rt_flag3_thread,
					"rt_flag3_thread",
					flag3_thread_entry,
					RT_NULL,
					&rt_flag3_thread_stack[0],
					sizeof(rt_flag3_thread_stack),
					4);
	/* ���̲߳��뵽�����б� */				
	rt_thread_startup(&rt_flag3_thread);
	


					
	/* ����ϵͳ������ */
	rt_system_scheduler_start();
	
}


/* �����ʱ */
void delay(rt_uint32_t count)
{
	while(count != 0)
		count --;
}

/* �߳�1 */
void flag1_thread_entry(void* p_arg)
{
	while(1)
	{
#if 0
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
		rt_schedule();
#else 
		flag1 = 1;
		rt_thread_delay(4);
		flag1 = 0;
		rt_thread_delay(4);
#endif
	}
}

/* �߳�2 */
void flag2_thread_entry(void* p_arg)
{
	while(1)
	{
#if 0
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
		rt_schedule();
#else
		flag2 = 1;
		rt_thread_delay(2);
		flag2 = 0;
		rt_thread_delay(2);
#endif
	}
}




/* �߳�3 */
void flag3_thread_entry(void* p_arg)
{
	while(1)
	{
		flag3 = 1;
		rt_thread_delay(3);
		flag3  =0;
		rt_thread_delay(3);
	}
}


void SysTick_Handler(void)
{
	
	/* �����ж� */
	rt_interrupt_enter();
	
	/* ʱ����� */
	rt_tick_increase();
	
	/* �뿪�ж� */
	rt_interrupt_leave();
	
}














