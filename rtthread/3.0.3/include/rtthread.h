#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

/* 包含的头文件 */
#include <rtdef.h>
#include <rtconfig.h>
#include <rtservice.h>



/*
-------------------------------------------------------------------------
*                               线程接口
-------------------------------------------------------------------------
*/

/* 线程创建函数 */
rt_err_t rt_thread_init(struct rt_thread *thread,
						void (*entry) (void *parameter),
						void                *parameter,
						void                *stack_start,
						rt_uint32_t          stack_size);

/*
-------------------------------------------------------------------------
*                             调度器接口
-------------------------------------------------------------------------
*/

/* 初始化系统调度器 */
void rt_system_scheduler_init(void);
/* 启动调度器函数 */	
void rt_system_scheduler_start(void);
/* 系统调度函数 */	
void rt_schedule(void);						
						
						
#endif  /* __RT_THREAD_H__ */




