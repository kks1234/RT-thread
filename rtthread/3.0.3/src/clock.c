#include <rtthread.h>
#include <rthw.h>





static rt_tick_t rt_tick = 0; /* 系统时基计数器 */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;


#if 0
/* 时基更新函数 */
void rt_tick_increase(void)
{
	rt_ubase_t i;
	struct rt_thread *thread;
	rt_tick ++;

#if 0
	/* 扫描就绪列表中的所有线程的remaining_tick ,如果不为0，则减1  */
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
	/* 系统调度 */
	rt_schedule();
}

#else

void rt_tick_increase(void)
{
	/* 系统时基计数器加 1 操作，rt_tick 是一个全局变量 */
	++ rt_tick;
	
	/* 扫描定时器列表 */
	rt_timer_check();
}

#endif




/* 获取时间变量的值 */
rt_tick_t rt_tick_get(void)
{
	return rt_tick;
}


































