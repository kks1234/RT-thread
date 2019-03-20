#ifndef __RT_DEF_H__
#define __RT_DEF_H__

#include <rtconfig.h>


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


/* maximum value of base type */
#define RT_UINT8_MAX                    0xff            /**< Maxium number of UINT8 */
#define RT_UINT16_MAX                   0xffff          /**< Maxium number of UINT16 */
#define RT_UINT32_MAX                   0xffffffff      /**< Maxium number of UINT32 */
#define RT_TICK_MAX                     RT_UINT32_MAX   /**< Maxium number of tick */




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




/* 对象枚举类型定义 */
enum rt_object_class_type
{
	RT_Object_Class_Thread = 0,                      /* 对象是线程 */
	RT_Object_Class_Semaphore,                       /* 对象是信号量 */
	RT_Object_Class_Mutex,                           /* 对象是互斥量 */
	RT_Object_Class_Event,                           /* 对象是事件 */
	RT_Object_Class_MailBox,                         /* 对象是邮箱 */ 
	RT_Object_Class_MessageQueue,                    /* 对象是消息队列 */
	RT_Object_Class_MemHeap,                         /* 对象是内存堆 */
	RT_Object_Class_MemPool,                         /* 对象是内存池 */
	RT_Object_Class_Device,                          /* 对象是设备 */
	RT_Object_Class_Timer,                           /* 对象是定时器 */
	RT_Object_Class_Module,                          /* 对象是模块 */
	RT_Object_Class_Unknown,                         /* 对象未知 */
	RT_Object_Class_Static = 0x80                    /* 对象是静态对象 */
};

/* 对象数据类型定义 */
struct rt_object
{
	char   name[RT_NAME_MAX];                        /* 内核对象的名字 */
	rt_uint8_t type;                                 /* 内核对象的类型 */
	rt_uint8_t flag;                                 /* 内核对象的状态 */
	         
	rt_list_t  list;                                 /* 内核对象的列表节点 */
};
typedef struct rt_object *rt_object_t;



/* 内核对象信息结构体 */   /* 容器的变量结构 */
struct rt_object_information
{
	enum rt_object_class_type type;                /* 对象类型 */
	rt_list_t          object_list;                /* 对象列表节点头 */
	rt_size_t          object_size;                /* 对象大小 */
};








/* 系统定时器列表 */
#ifndef RT_TIMER_SKIP_LIST_LEVEL

#define RT_TIMER_SKIP_LIST_LEVEL                  1

#endif

#ifndef RT_TIMER_SKIP_LIST_MASK
#define RT_TIMER_SKIP_LIST_MASK         0x3
#endif


/**
 * 定时器结构体
 */

struct rt_timer
{
	struct rt_object             parent;     /* 从 rt_object 继承 */
	
	rt_list_t row[RT_TIMER_SKIP_LIST_LEVEL]; /* 节点 */

	void (*timeout_func) (void *parameter);  /* 超时函数 */
	void         *parameter;                 /* 超时函数形参 */
	
	rt_tick_t    init_tick;                  /* 定时器实际需要延时的时间 */
	rt_tick_t    timeout_tick;               /* 定时器实际超时的系统节拍数 */
};

typedef struct rt_timer *rt_timer_t;        





/* 线程控制块类型声明 */
/* ps：不完整 后续补全 */

struct rt_thread
{
	/* rt 对象 */
	char   name[RT_NAME_MAX];             /* 内核对象的名字 */

	rt_uint8_t type;                      /* 内核对象的类型 */
	rt_uint8_t flags;                      /* 内核对象的状态 */        
	rt_list_t  list;                      /* 内核对象的列表节点 */	
	
	rt_list_t tlist ;                     /* 线程链表节点 */	
	void    *sp ;     		              /* 线程栈指针 */
	void    *entry ;  		              /* 线程入口地址 */

	void    *parameter ;	              /* 线程形参 */
	void    *stack_addr ;                 /* 线程栈起始地址 */
	rt_uint32_t stack_size ;              /* 线程栈大小，单位为字节 */
		
	rt_ubase_t   init_tick;               /* 初始化时间片 */
	rt_ubase_t   remaining_tick;          /* 剩余时间片 */
	
	rt_uint8_t   current_priority;        /* 当前优先级 */
	rt_uint8_t   init_priority;           /* 初始优先级 */
	rt_uint32_t  number_mask;             /* 当前优先级掩码 */
	
	rt_err_t     error;                   /* 错误码 */
	rt_uint8_t   stat;                    /* 线程的状态 */
	
	struct rt_timer thread_timer;         /* 内置的线程定时器 */
}; 

typedef struct rt_thread *rt_thread_t ;


/*
*************************************************************************************
*                                   错误码定义     
*************************************************************************************
*/
/* RT-Thread错误码重定义 */
#define RT_EOK                                0              /**< There is no error */
#define RT_ERROR                              1              /**< A generic error happens */
#define RT_ETIMEOUT                           2              /**< Timed out */
#define RT_EFULL                              3              /**< The resource is full */
#define RT_EEMPTY                             4              /**< The resource is empty */
#define RT_ENOMEM                             5              /**< No memory */
#define RT_ENOSYS                             6              /**< No system */
#define RT_EBUSY                              7              /**< Busy */
#define RT_EIO                                8              /**< IO error */
#define RT_EINTR                              9              /**< Interrupted system call */
#define RT_EINVAL                             10             /**< Invalid argument */



/*
***********************************************************************************
*                                   线程状态定义 
***********************************************************************************
*/

#define RT_THREAD_INIT                            0x00                        /* 初始状态 */
#define RT_THREAD_READY                           0x01                        /* 就绪状态 */
#define RT_THREAD_SUSPEND                         0x02                        /* 挂起状态 */
#define RT_THREAD_RUNNING                         0x03                        /* 运行状态 */
#define RT_THREAD_BLOCK                           RT_THREAD_SUSPEND           /* 阻塞状态 */
#define RT_THREAD_CLOSE                           0x04                        /* 关闭状态 */
#define RT_THREAD_STAT_MASK                       0x0f

#define RT_THREAD_STAT_SIGNAL                     0x10
#define RT_THREAD_STAT_SIGNAL_READY               (RT_THREAD_STAT_SIGNAL | RT_THREAD_READY)
#define RT_THREAD_STAT_SIGNAL_SUSPEND             0x20
#define RT_THREAD_STAT_SIGNAL_MASK                0xf0




/*
***********************************************************************************
*                                   定时器状态定义 
***********************************************************************************
*/

#define RT_TIMER_FLAG_DEACTIVATED                      0x0       /* 定时器没有激活 */
#define RT_TIMER_FLAG_ACTIVATED                        0x1       /* 定时器已经激活 */
#define RT_TIMER_FLAG_ONE_SHOT                         0x0       /* 单次定时 */
#define RT_TIMER_FLAG_PERIODIC                         0x2       /* 周期定时 */

#define RT_TIMER_FLAG_HARD_TIMER                       0x0       /* 硬件定时器，定时器回调函数在 tick isr 中调用 */

#define RT_TIMER_FLAG_SOFT_TIMER                       0x4       /* 软件定时器，定时器回调函数在定时器线程中调用 */


/*
***********************************************************************************
*                                   定时器控制命令宏定义 
***********************************************************************************
*/


#define RT_TIMER_CTRL_SET_TIME                         0x0       /* 设置定时器时间 */
#define RT_TIMER_CTRL_GET_TIME                         0x1       /* 获取定时器的定时时间 */
#define RT_TIMER_CTRL_SET_ONESHOT                      0x2       /* 修改定时器为一次定时 */
#define RT_TIMER_CTRL_SET_PERIODIC                     0x3       /* 修改定时器为周期定时 */














#endif  /* __RT_DEF_H__ */


















