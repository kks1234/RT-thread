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
						rt_uint32_t          stack_size)
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











