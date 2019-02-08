#include <rtthread.h>


/*
*************************************************************************
*                                 ȫ�ֱ���
*************************************************************************
*/



	/* PendSV�жϷ�����ִ�б�־ */
	rt_uint32_t rt_thread_switch_interrupt_flag;
	/* ���ڴ洢��һ���̵߳�ջ��sp��ָ�� */
	rt_uint32_t rt_interrupt_from_thread;
	/* ���ڴ洢��һ����Ҫ���е��̵߳�ջ��sp��ָ�� */
	rt_uint32_t rt_interrupt_to_thread;
	
	
	
	
	
	
/*
*************************************************************************
*                                 ��������
*************************************************************************
*/

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





/*
*************************************************************************
*                                 ����ʵ��
*************************************************************************
*/

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
	stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk,8);
	
	/* stk ָ����������ƶ�sizeof(struct stack_frame)��ƫ�� */   /* ??? */
	stk -= sizeof(struct stack_frame);
	
	/* ��stkǿ��ת����stack_frame���ͺ�浽stack_frame */
	stack_frame = (struct stack_frame*)stk;
	
	/* ��stack_frame Ϊ��ʼ��ַ,ռ�ռ������sizeof(struct stack_frame)���ڴ�
	 ��ʼ��Ϊ 0xdeadbeef*/
	for(i = 0 ; i < sizeof(struct stack_frame)/sizeof(rt_uint32_t) ; i ++)
	{
		((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
	}
	
	/* ��ʼ���쳣����ʱ�Զ�����ļĴ��� */
	stack_frame->exception_stack_frame.r0 = (unsigned long)parameter; /* r0 : argument */
	stack_frame->exception_stack_frame.r1 = 0;   /* r1 */
	stack_frame->exception_stack_frame.r2 = 0;   /* r2 */
	stack_frame->exception_stack_frame.r3 = 0;   /* r3 */
	stack_frame->exception_stack_frame.r12 = 0;   /* r12 */
	stack_frame->exception_stack_frame.lr = 0;   /* lr ��ʱ��ʼ��Ϊ0 */
	stack_frame->exception_stack_frame.pc = (unsigned long)tentry;  /* entry */
	stack_frame->exception_stack_frame.psr = 0x01000000L;    /* PSR */
	
	/* �����߳�ջָ�� */
	return stk;
}









