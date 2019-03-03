#include <rtthread.h>
#include <rthw.h>
/* 2019.03.02 */



/* 线程就绪列表 */
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];


#define IDLE_THREAD_STACK_SIZE       512


ALIGN(RT_ALIGN_SIZE)


/* 定义空闲线程栈 */
static rt_uint8_t rt_thread_stack[IDLE_THREAD_STACK_SIZE];

/* 空闲线程的线程控制块 */
struct rt_thread idle;

/* 在RT-Thread中空闲线程函数主要做一些系统内存清理工作，本章只实现对一个全局变量进行计数 */


rt_ubase_t  rt_idletask_ctr = 0;

/* 空闲线程函数 */

void rt_thread_idle_entry(void *parameter)
{
	parameter = parameter;
	while(1)
	{
		rt_idletask_ctr ++;
	}
}



/* 空闲线程初始化函数 */
void rt_thread_idle_init(void)
{
	
	/* 初始化线程 */
	rt_thread_init(&idle,
					"idle",
					rt_thread_idle_entry,
					RT_NULL,
					&rt_thread_stack[0],
					sizeof(rt_thread_stack));
	
	/* 将线程插入就绪列表 */  /* 空闲线程默认最低优先级 */
	rt_list_insert_before( &(rt_thread_priority_table[RT_THREAD_PRIORITY_MAX-1]),
							&(idle.list));
	
}



















