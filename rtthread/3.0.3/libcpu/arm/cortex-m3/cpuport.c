#include <rtthread.h>


/*
*************************************************************************
*                                 全局变量
*************************************************************************
*/



	/* PendSV中断服务函数执行标志 */
	rt_uint32_t rt_thread_switch_interrupt_flag;
	/* 用于存储上一个线程的栈的sp的指针 */
	rt_uint32_t rt_interrupt_from_thread;
	/* 用于存储下一个将要运行的线程的栈的sp的指针 */
	rt_uint32_t rt_interrupt_to_thread;
	
	
	
	
	
	
/*
*************************************************************************
*                                 数据类型
*************************************************************************
*/

struct exception_stack_frame
{
	/* 异常发生时,自动加载到CPU寄存器中的内容 */
	rt_uint32_t    r0;
	rt_uint32_t    r1;
	rt_uint32_t    r2;
	rt_uint32_t    r3;
	rt_uint32_t    r12;
	rt_uint32_t    lr;  /* 链接寄存器， 程序调用返回地址 r14*/
	rt_uint32_t    pc;  /* 程序计数器， 指向当前指令的下条指令的地址 r15*/
	rt_uint32_t    psr;	/* 程序状态寄存器 */
};

struct stack_frame
{
	/*  异常发生时,需手动加载到CPU寄存器的内容 */ 
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
*                                 函数实现
*************************************************************************
*/

/* 初始化线程栈,并返回栈顶指针 */ 
rt_uint8_t *rt_hw_stack_init(void       *tentry,
							 void       *parameter,
						     rt_uint8_t *stack_addr)
{
	struct stack_frame *stack_frame;
	rt_uint8_t         *stk;
	unsigned long       i;
	
	
	/* 获取栈顶指针
	 rt_hw_stack_init 在调用的时候，传给 stack_addr 的是(栈顶指针 - 4 )*/
	stk = stack_addr + sizeof(rt_uint32_t) ;
	
	/* 让 stk 向下8字节对齐 */
	stk = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)stk,8);
	
	/* stk 指针继续向下移动sizeof(struct stack_frame)个偏移 */   /* ??? */
	stk -= sizeof(struct stack_frame);
	
	/* 将stk强制转化成stack_frame类型后存到stack_frame */
	stack_frame = (struct stack_frame*)stk;
	
	/* 以stack_frame 为起始地址,占空间里面的sizeof(struct stack_frame)个内存
	 初始化为 0xdeadbeef*/
	for(i = 0 ; i < sizeof(struct stack_frame)/sizeof(rt_uint32_t) ; i ++)
	{
		((rt_uint32_t *)stack_frame)[i] = 0xdeadbeef;
	}
	
	/* 初始化异常发生时自动保存的寄存器 */
	stack_frame->exception_stack_frame.r0 = (unsigned long)parameter; /* r0 : argument */
	stack_frame->exception_stack_frame.r1 = 0;   /* r1 */
	stack_frame->exception_stack_frame.r2 = 0;   /* r2 */
	stack_frame->exception_stack_frame.r3 = 0;   /* r3 */
	stack_frame->exception_stack_frame.r12 = 0;   /* r12 */
	stack_frame->exception_stack_frame.lr = 0;   /* lr 暂时初始化为0 */
	stack_frame->exception_stack_frame.pc = (unsigned long)tentry;  /* entry */
	stack_frame->exception_stack_frame.psr = 0x01000000L;    /* PSR */
	
	/* 返回线程栈指针 */
	return stk;
}









