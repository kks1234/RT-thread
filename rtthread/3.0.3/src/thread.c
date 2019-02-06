#include <rtthread.h>
#include <rthw.h>


/* �̴߳������� */
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
	
	/* ��ʼ���߳�ջ,�������߳�ջָ�� */
	
	
	
	
	return RT_EOK;
}
