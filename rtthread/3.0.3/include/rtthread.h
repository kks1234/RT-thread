#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

/* 包含的头文件 */
#include <rtdef.h>
#include <rtconfig.h>
#include <rtservice.h>





/*
-------------------------------------------------------------------------
*                               内核对象接口
-------------------------------------------------------------------------
*/
void rt_object_init(struct rt_object         *object,
                    enum rt_object_class_type type,
                    const char               *name);


/*
-------------------------------------------------------------------------
*                             空闲线程接口
-------------------------------------------------------------------------
*/

void rt_thread_idle_init(void);



/*
-------------------------------------------------------------------------
*                               线程接口
-------------------------------------------------------------------------
*/

/* 线程创建函数 */
rt_err_t rt_thread_init(struct rt_thread *thread,
						const char          *name,
						void (*entry) (void *parameter),
						void                *parameter,
						void                *stack_start,
						rt_uint32_t          stack_size);
						
						
void rt_thread_delay(rt_tick_t tick);
						
						

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
						


/*
-------------------------------------------------------------------------
*                             内核服务相关函数接口
-------------------------------------------------------------------------
*/                        
                        
char *rt_strncpy(char *dst, const char *src, rt_ubase_t n); 












#endif  /* __RT_THREAD_H__ */




