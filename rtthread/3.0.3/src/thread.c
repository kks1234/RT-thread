#include <rtthread.h>
#include <rthw.h>


/* 当前线程控制块指针 */
extern struct rt_thread *rt_current_thread;



/* 线程创建函数 */
rt_err_t rt_thread_init(struct rt_thread *thread,
						const char          *name,
						void (*entry) (void *parameter),
						void                *parameter,
						void                *stack_start,
						rt_uint32_t          stack_size,
						rt_uint8_t           priority)
{
	/* 线程对象初始化 */
	/* 线程结构体开头部分的4个成员就是 rt_object_t 成员 */
	rt_object_init((rt_object_t)thread, RT_Object_Class_Thread, name);
	
	
	rt_list_init(&(thread->tlist));
	
	thread->entry = (void*)entry;
	thread->parameter = parameter;
	
	thread->stack_addr = stack_start;
	thread->stack_size = stack_size;
	
	/* 初始化线程栈,并返回线程栈指针 */
	thread->sp = 
	(void *)rt_hw_stack_init( thread->entry,
							  thread->entry,
	(void *)( (char *)thread->stack_addr + thread->stack_size - 4) ) ;
	
	/* 设置优先级 */
	thread->init_priority    = priority;
	thread->current_priority = priority;
	thread->number_mask = 0;
	
	/* 错误码状态 */
	thread->error = RT_EOK;
	thread->stat = RT_THREAD_INIT;
	
	return RT_EOK;
}




/* 阻塞延时函数 */
void rt_thread_delay(rt_tick_t tick)
{
	struct rt_thread *thread;
	
	/* 获取当前线程的线程控制块 */
	thread = rt_current_thread;
	
	/* 设置延时时间 */
	thread->remaining_tick = tick;
	
	/* 进行系统调度 */
	rt_schedule();
}


/* 线程启动函数 */
rt_err_t rt_thread_startup(rt_thread_t thread)
{
	/* 设置当前优先级为初始优先级 */
	thread->current_priority = thread->init_priority;
	thread->number_mask = 1L << thread->current_priority;
	
	/* 改变线程的状态为挂起状态 */
	thread->stat = RT_THREAD_SUSPEND;
	/* 然后恢复线程 */
	rt_thread_resume(thread);
	
	if(rt_thread_self() != RT_NULL)
	{
		/* 系统调度 */
		rt_schedule();
	}
	
	return RT_EOK;
}


/* 线程恢复函数 */
rt_err_t rt_thread_resume(rt_thread_t thread)
{
	register rt_base_t temp;
	
	/* 将要恢复的线程必须在挂起状态，否则返回错误码 */
	if((thread->stat & RT_THREAD_STAT_MASK) != RT_THREAD_SUSPEND)
	{
		return -RT_ERROR;
	}		
	
	/* 关中断 */
	temp = rt_hw_interrupt_disable();
	
	/* 从挂起队列移除 */
	rt_list_remove(&(thread->tlist));
	
	/* 开中断 */
	rt_hw_interrupt_enable(temp);
	
	/* 插入就绪列表 */
	rt_schedule_insert_thread(thread);
	
	return RT_EOK;
	
}

/* 返回当前线程的指针 */
rt_thread_t rt_thread_self(void)
{
	return rt_current_thread;
}




