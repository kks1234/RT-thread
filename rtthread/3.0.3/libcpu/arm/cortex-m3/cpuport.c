#include <rtthread.h>


struct exception_stack_frame
{
	/* �쳣����ʱ,�Զ����ص�CPU�Ĵ����е����� */
	rt_uint32_t    r0;
	rt_uint32_t    r1;
	rt_uint32_t    r2;
	rt_uint32_t    r3;
	rt_uint32_t    r12;
	rt_uint32_t    lr;  /* ���ӼĴ����� ������÷��ص�ַ r14*/
	rt_uint32_t    pc;  /* ����������� ָ��ǰָ�������ָ��ĵ�ַ r15*/
	rt_uint32_t    psr;	/* ����״̬�Ĵ��� */
};

struct stack_frame
{
	/*  �쳣����ʱ,���ֶ����ص�CPU�Ĵ��������� */ 
	rt_uint32_t    r4;
	rt_uint32_t    r5;
	rt_uint32_t    r6;
	rt_uint32_t    r7;
	rt_uint32_t    r8;
	rt_uint32_t    r9;
	rt_uint32_t    r10;
	rt_uint32_t    r11;
	
	struct exception_stack_frame exception_stack_frame;
};




/* ��ʼ���߳�ջ,������ջ��ָ�� */ 
rt_uint8_t *rt_hw_stack_init(void       *tentry,
							 void       *parameter,
						     rt_uint8_t *stack_addr)
{
	struct stack_frame *stack_frame;
	rt_uint8_t         *stk;
	unsigned long       i;
	
	
	/* ��ȡջ��ָ��
	 rt_hw_stack_init �ڵ��õ�ʱ�򣬴��� stack_addr ����(ջ��ָ�� - 4 )*/
	stk = stack_addr + sizeof(rt_uint32_t) ;
	
	/* �� stk ����8�ֽڶ��� */
	

	
	
}









