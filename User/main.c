#include <rtthread.h>


/* �߳̾����б� */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

/* ����ȫ�ֱ��� */
rt_uint8_t flag1;
rt_uint8_t flag2;

ALIGN(RT_ALIGN_SIZE)



/* �����߳�ջ */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];


/* �����߳̿��ƿ� */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


/* �̺߳������� */
void flag1_thread_entry(void* p_arg);
void flag2_thread_entry(void* p_arg);
/* �����ʱ�������� */
void delay(rt_uint32_t count);






int  main()
{
	/* Ӳ����ʼ�� */
	/* ��Ӳ����س�ʼ�������� �����������û����س�ʼ������ */
	
	
	
	/* ��������ʼ�� */
	rt_system_scheduler_init();
	
	
	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag1_thread,
					flag1_thread_entry,
					RT_NULL,
					&rt_flag1_thread_stack[0],
					sizeof(rt_flag1_thread_stack));
	/* ���̲߳��뵽�����б� */
	rt_list_insert_before(&(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist));
	
	
	/* ��ʼ���߳� */
	rt_thread_init( &rt_flag2_thread,
					flag2_thread_entry,
					RT_NULL,
					&rt_flag2_thread_stack[0],
					sizeof(rt_flag2_thread_stack));	
	/* ���̲߳��뵽�����б� */
	rt_list_insert_before(&(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist));
	
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
		flag1 = 1;
		delay(100);
		flag1 = 0;
		delay(100);
	}
}

/* �߳�2 */
void flag2_thread_entry(void* p_arg)
{
	while(1)
	{
		flag2 = 1;
		delay(100);
		flag2 = 0;
		delay(100);
	}
}