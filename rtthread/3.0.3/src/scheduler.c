#include <rtthread.h>





/* ��ǰ�߳̿��ƿ�ָ�� */
struct rt_thread *rt_current_thread;

/* �߳̾����б� */
rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];



void rt_system_scheduler_init(void)
{
	register rt_base_t offset;
	
	for(offset = 0 ; offset < RT_THREAD_PRIORITY_MAX ; offset ++)
	{
		rt_list_init(&rt_thread_priority_table[offset]);
	}
	
	/* ��ʼ����ǰ�߳̿��ƿ�ָ�� */
	rt_current_thread = RT_NULL ;
}


/* �������������� */	
void rt_system_scheduler_start(void)
{
	register struct rt_thread *to_rhtead;
	
	
	/* �ֶ�ָ����һ�����еĽ��� */
	to_rhtead = rt_list_entry(rt_thread_priority_table[0].next,
							  struct rt_thread,
							  tlist);
	
	rt_current_thread = to_rhtead;
	
	/* �л���һ���߳�,�ú�����context_rvds.sʵ��,
	   ��rthw.h����,����ʵ�ֵ�һ���߳��л���
	   ��һ����ຯ����C�ļ��е��õ�ʱ��,������β�,
	   ��ִ�е�ʱ��Ὣ�βδ��뵽CPU�Ĵ���r0 */
	rt_hw_context_switch_to((rt_uint32_t)&to_rhtead->sp)						  
}











