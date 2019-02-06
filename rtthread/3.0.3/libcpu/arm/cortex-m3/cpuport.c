#include <rtthread.h>


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
	

	
	
}









