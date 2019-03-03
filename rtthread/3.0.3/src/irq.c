#include <rtthread.h>
#include <rthw.h>


volatile rt_uint8_t rt_interrupt_nest;

/**
 * 当bsp文件中的终端服务函数进入中断时会调用该函数
 *
 * 请不要在应用程序中调用该函数
 *
 */
void rt_interrupt_enter(void)
{
	rt_base_t level ;
	
	/* 关中断 */
	level = rt_hw_interrupt_disable();
	
	/* 中断计数器 ++ */
	rt_interrupt_nest ++;
	
	/* 开中断 */
	rt_hw_interrupt_enable(level);
	
}


/**
 * 当bsp文件中的终端服务函数离开中断时会调用该函数
 *
 * 请不要在应用程序中调用该函数
 *
 */

void rt_interrupt_leave(void)
{
	rt_base_t level;
	
	/* 关中断 */
	level = rt_hw_interrupt_disable();
	
	/* 中断计数器 -- */
	rt_interrupt_nest --;
	
	/* 开中断 */
	rt_hw_interrupt_enable(level);
	
}






































































