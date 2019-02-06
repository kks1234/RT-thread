#ifndef __RT_HW_H__
#define __RT_HW_H__

#include <rtthread.h>










/* 初始化线程栈,并返回栈顶指针 */ 
rt_uint8_t *rt_hw_stack_init(void       *tentry,
							 void       *parameter,
						     rt_uint8_t *stack_addr);






#endif  /* __RT_HW_H__ */





