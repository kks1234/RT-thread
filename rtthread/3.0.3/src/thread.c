#include <rtthread.h>
#include <rthw.h>


/* 线程创建函数 */
rt_err_t rt_thread_init(struct rt_thread *thread,
						void (*entry) (void *parameter),
						void                *parameter,
						void                *stack_start,
						rt_uint32_t          stack_size)
{
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
















