#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

/* 包含的头文件 */
#include <rtdef.h>
#include <rtconfig.h>
#include <rtservice.h>





/*
-------------------------------------------------------------------------
*                              定时器接口
-------------------------------------------------------------------------
*/

/* 定时器表初始化 */
void rt_system_timer_init(void);

/* 定时器初始化函数 */
void rt_timer_init(rt_timer_t timer,
					const char *name,
					void (*timeout) (void *parameter),
					void    *parameter,
					rt_tick_t   time,
					rt_uint8_t  flag);

/* 定时器停止函数 */
rt_err_t rt_timer_stop(rt_timer_t timer);

/* 定时器控制函数 */
rt_err_t rt_timer_control(rt_timer_t timer, int cmd, void *arg);
					
/* 定时器启动函数 */
rt_err_t rt_timer_start(rt_timer_t timer);

/* 定时器扫描函数 */					
void rt_timer_check(void);					
					
					
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
						rt_uint32_t          stack_size,
						rt_uint8_t           priority);

/* 线程休眠函数 */
rt_err_t rt_thread_sleep(rt_tick_t tick);
						
/* 阻塞延时函数 */						
rt_err_t rt_thread_delay(rt_tick_t tick);

/*调度器插入线程*/						                        
void rt_schedule_insert_thread(struct rt_thread *thread);

/* 调度器删除线程 */						
void rt_schedule_remove_thread(struct rt_thread *thread);
						
/* 线程启动函数 */
rt_err_t rt_thread_startup(rt_thread_t thread);
						
/* 恢复线程函数 */
rt_err_t rt_thread_resume(rt_thread_t thread);
			
/* 线程挂起函数 */
rt_err_t rt_thread_suspend(rt_thread_t thread);

/* 返回当前线程的指针 */						
rt_thread_t rt_thread_self(void); 
	
/* 超时函数接口 */
void rt_thread_timeout(void *parameter); 



/*
-------------------------------------------------------------------------
*                             时钟相关接口
-------------------------------------------------------------------------
*/ 						

/* 时基更新函数 */						
void rt_tick_increase(void);

/* 获取时间变量的值 */
rt_tick_t rt_tick_get(void);						
						
						
						
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

/* 优先级查找函数 */
int __rt_ffs(int value);





/*
-------------------------------------------------------------------------
*                             中断接口
-------------------------------------------------------------------------
*/

void rt_interrupt_enter(void);

void rt_interrupt_leave(void);




#endif  /* __RT_THREAD_H__ */




