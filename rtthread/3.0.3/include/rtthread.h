#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

/* 包含的头文件 */
#include <rtdef.h>
#include <rtconfig.h>
#include <rtservice.h>



/* 线程创建函数 */
rt_err_t rt_thread_init(struct rt_thread *thread,
						void (*entry) (void *parameter),
						void                *parameter,
						void                *stack_start,
						rt_uint32_t          stack_size);






#endif  /* __RT_THREAD_H__ */




