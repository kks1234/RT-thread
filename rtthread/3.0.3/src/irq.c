#include <rtthread.h>
#include <rthw.h>


volatile rt_uint8_t rt_interrupt_nest;

/**
 * ��bsp�ļ��е��ն˷����������ж�ʱ����øú���
 *
 * �벻Ҫ��Ӧ�ó����е��øú���
 *
 */
void rt_interrupt_enter(void)
{
	rt_base_t level ;
	
	/* ���ж� */
	level = rt_hw_interrupt_disable();
	
	/* �жϼ����� ++ */
	rt_interrupt_nest ++;
	
	/* ���ж� */
	rt_hw_interrupt_enable(level);
	
}


/**
 * ��bsp�ļ��е��ն˷������뿪�ж�ʱ����øú���
 *
 * �벻Ҫ��Ӧ�ó����е��øú���
 *
 */

void rt_interrupt_leave(void)
{
	rt_base_t level;
	
	/* ���ж� */
	level = rt_hw_interrupt_disable();
	
	/* �жϼ����� -- */
	rt_interrupt_nest --;
	
	/* ���ж� */
	rt_hw_interrupt_enable(level);
	
}






































































