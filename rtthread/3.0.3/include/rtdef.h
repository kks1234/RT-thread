#ifndef __RT_DEF_H__
#define __RT_DEF_H__

/*
************************************************************************************
*                               数据类型                                 
************************************************************************************
*/
/* RT-Thread基础数据类型定义 */

typedef signed    char                             rt_int8_t;
typedef signed    short                            rt_int16_t;
typedef signed    long                             rt_int32_t;
typedef unsigned  char                             rt_uint8_t;
typedef unsigned  short                            rt_uint16_t;
typedef unsigned  long                             rt_uint32_t;
typedef int                                        rt_bool_t;

/* 32bit CPU */

typedef long                                       rt_base_t;
typedef unsigned  long                             rt_ubase_t;

typedef rt_base_t                                  rt_err_t;
typedef rt_uint32_t                                rt_time_t;
typedef rt_uint32_t                                rt_tick_t;
typedef rt_base_t                                  rt_flag_t;
typedef rt_ubase_t                                 rt_size_t;
typedef rt_ubase_t                                 rt_dev_t;
typedef rt_base_t                                  rt_off_t;

/* 布尔数据类型重定义 */ 
#define RT_TURE                                    1
#define RT_FALSE                                   0

#ifdef __CC_ARM
#define rt_inline                                  static __inline
#define ALIGN(n)                                   __attribute__((aligned(n)))

#elif defined (__IAR_SYSTEM_ICC__)
#define rt_inline                                  static inline
#define ALIGN(n)                                   PRAGMA(data_alignment=n)

#elif defined (__GNUC__)
#define rt_inline                                  static __inline
#define ALIGN(n)                                   __attribute__((aligned(n)))
#else
#error not supported tool chain
#endif


#define RT_ALIGN(size,align)                       (((size) + (align) - 1) & ~((align) - 1))
#define RT_ALIGN_DOWN(size,align)                  ((size) & ~((align) - 1))


#define RT_NULL                                    (0)




/* 双向链表节点数据类型 rt_list_t 定义 */ 
struct rt_list_node
{
	struct rt_list_node *next ;   /* 指向后一个节点 */
	struct rt_list_node *prev ;   /* 指向前一个节点 */
};
typedef struct rt_list_node rt_list_t;


/* 线程控制块类型声明 */
/* ps：不完整 后续补全 */

struct rt_thread
{
	void    *sp ;     		 /* 线程栈指针 */
	void    *entry ;  		 /* 线程入口地址 */
	void    *parameter ;	 /* 线程形参 */
	void    *stack_addr ;    /* 线程栈起始地址 */
	rt_uint32_t stack_size ; /* 线程栈大小，单位为字节 */
	rt_list_t tlist ;        /* 线程链表节点 */
};

typedef struct rt_thread *rt_thread_t ;






#endif  /* __RT_DEF_H__ */


















