#ifndef __RT_HW_H__
#define __RT_HW_H__

#include <rtthread.h>










/* 初始化线程栈,并返回栈顶指针 */ 
rt_uint8_t *rt_hw_stack_init(void       *tentry,
							 void       *parameter,
						     rt_uint8_t *stack_addr);



/* 线程切换函数 */
void rt_hw_context_switch_to(rt_uint32_t to);
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to);	
							 
/* 关中断 */
rt_base_t rt_hw_interrupt_disable(void);							 
/* 开中断 */	 
void rt_hw_interrupt_enable(rt_base_t level);					 
							 
							 

#endif  /* __RT_HW_H__ */





