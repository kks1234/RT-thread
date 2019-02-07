#include <rtthread.h>


/* 线程就绪列表 */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

/* 定义全局变量 */
rt_uint8_t flag1;
rt_uint8_t flag2;

ALIGN(RT_ALIGN_SIZE)



/* 定义线程栈 */
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];


/* 定义线程控制块 */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;


/* 线程函数声明 */
void flag1_thread_entry(void* p_arg);
void flag2_thread_entry(void* p_arg);
/* 软件延时函数声明 */
void delay(rt_uint32_t count);






int  main()
{
	/* 硬件初始化 */
	/* 将硬件相关初始化放在这 若软件仿真则没有相关初始化代码 */
	
	
	
	/* 调度器初始化 */
	rt_system_scheduler_init();
	
	
	/* 初始化线程 */
	rt_thread_init( &rt_flag1_thread,
					flag1_thread_entry,
					RT_NULL,
					&rt_flag1_thread_stack[0],
					sizeof(rt_flag1_thread_stack));
	/* 将线程插入到就绪列表 */
	rt_list_insert_before(&(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist));
	
	
	/* 初始化线程 */
	rt_thread_init( &rt_flag2_thread,
					flag2_thread_entry,
					RT_NULL,
					&rt_flag2_thread_stack[0],
					sizeof(rt_flag2_thread_stack));	
	/* 将线程插入到就绪列表 */
	rt_list_insert_before(&(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist));
	
}


/* 软件延时 */
void delay(rt_uint32_t count)
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