




/* 定义全局变量 */
rt_uint8_t flag1;
rt_uint8_t flag2;

ALIGN(RT_ALIGN_SIZE)



/* 定义线程栈 */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread+stack[512];


/* 定义线程控制块 */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


/* 线程函数声明 */
void flag1_thread_entry(void* p_arg);
void flag2_thread_entry(void* p_arg);
/* 软件延时函数声明 */
void delay(uint32_t count);






int  main()
{
	


	
}


/* 软件延时 */
void delay(uint32_t count)
{
	while(count != 0)
		count --;
}

/* 线程1 */
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

/* 线程2 */
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