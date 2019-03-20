#include <rtthread.h>
#include <rthw.h>





static rt_tick_t rt_tick = 0; /* ϵͳʱ�������� */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;


#if 0
/* ʱ�����º��� */
void rt_tick_increase(void)
{
	rt_ubase_t i;
	struct rt_thread *thread;
	rt_tick ++;

#if 0
	/* ɨ������б��е������̵߳�remaining_tick ,�����Ϊ0�����1  */
	for(i=0; i<RT_THREAD_PRIORITY_MAX; i++)
	{
		thread = rt_list_entry( rt_thread_priority_table[i].next,
								struct rt_thread,
								tlist);
		if(thread->remaining_tick > 0)
		{
			thread->remaining_tick --;
		}
	}
#else
	
	for(i=0; i<RT_THREAD_PRIORITY_MAX; i++)
	{
		thread = rt_list_entry( rt_thread_priority_table[i].next,
								struct rt_thread,
								tlist);
		if(thread->remaining_tick > 0)
		{
			thread->remaining_tick --;
			if(thread->remaining_tick == 0)
			{
				//rt_schedule_insert_thread(thread);
				rt_thread_ready_priority_group |= thread->number_mask;
			}
		}
	}
#endif
	/* ϵͳ���� */
	rt_schedule();
}

#else

void rt_tick_increase(void)
{
	struct rt_thread *thread;
	/* ϵͳʱ���������� 1 ������rt_tick ��һ��ȫ�ֱ��� */
	++ rt_tick;
	
	/* ��ȡ��ǰ�߳̿��ƿ� */
	thread = rt_thread_self();
	
	/* ʱ��Ƭ�ݼ� */
	-- thread->remaining_tick;
	
	/* ���ʱ��Ƭ����������ʱ��Ƭ��Ȼ���ó������� */
	if(thread->remaining_tick == 0)
	{
		/* ����ʱ��Ƭ */
		thread->remaining_tick = thread->init_tick;
		
		/* �ó������� */
		rt_thread_yield();
	}
	
	
	
	
	
	/* ɨ�趨ʱ���б� */
	rt_timer_check();
}

#endif




/* ��ȡʱ�������ֵ */
rt_tick_t rt_tick_get(void)
{
	return rt_tick;
}


































