




/* ����ȫ�ֱ��� */
rt_uint8_t flag1;
rt_uint8_t flag2;

ALIGN(RT_ALIGN_SIZE)



/* �����߳�ջ */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread+stack[512];


/* �����߳̿��ƿ� */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


/* �̺߳������� */
void flag1_thread_entry(void* p_arg);
void flag2_thread_entry(void* p_arg);
/* �����ʱ�������� */
void delay(uint32_t count);






int  main()
{
	


	
}


/* �����ʱ */
void delay(uint32_t count)
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