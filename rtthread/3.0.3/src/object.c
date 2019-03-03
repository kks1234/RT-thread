#include <rtthread.h>
#include <rthw.h>







/* �������������±궨��,����������С */
enum rt_object_info_type
{
	RT_Object_Info_Thread = 0,                       /* �������߳� */
#ifdef RT_USING_SEMAPHORE
	RT_Object_Info_Semaphore,                        /* �������ź��� */
#endif    
#ifdef RT_USING_MUTEX
	RT_Object_Info_Mutex,                            /* �����ǻ����� */
#endif
#ifdef RT_USING_EVENT
	RT_Object_Info_Event,                            /* �������¼� */
#endif
#ifdef RT_USING_MAILBOX
	RT_Object_Info_MailBox,                          /* ���������� */ 
#endif
#ifdef RT_USING_MESSAGEQUEUE
	RT_Object_Info_MessageQueue,                     /* ��������Ϣ���� */
#endif  
#ifdef RT_USING_MEMHEAP
	RT_Object_Info_MemHeap,                          /* �������ڴ�� */
#endif
#ifdef RT_USING_MEMPOOL
	RT_Object_Info_MemPool,                          /* �������ڴ�� */
#endif
#ifdef RT_USING_DEVICE
	RT_Object_Info_Device,                           /* �������豸 */
#endif
	RT_Object_Info_Timer,                            /* �����Ƕ�ʱ�� */
#ifdef RT_USING_MODULE
	RT_Object_Info_Module,                           /* ������ģ�� */
#endif
	RT_Object_Info_Unknown,                          /* ����δ֪ */
};


#define _OBJ_CONTAINER_LIST_INIT(c)     \
	{ &(rt_object_container[c].object_list), &(rt_object_container[c].object_list) }
	
	


/* rtt �����Ķ��� */

static struct rt_object_information
rt_object_container[RT_Object_Info_Unknown] = {
	/* ��ʼ����������  -  �߳� */
	{
		RT_Object_Class_Thread,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Thread),
		sizeof(struct rt_thread)
	},
		
#ifdef RT_USING_SEMAPHORE
	/* ��ʼ����������  -  �ź��� */
	{
		RT_Object_Class_Semaphore,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Semaphore),  
		sizeof(struct rt_semaphore)
	},
#endif
    
#ifdef RT_USING_MUTEX
	/* ��ʼ����������  -  ������ */
	{
		RT_Object_Class_Mutex,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Mutex),
		sizeof(struct rt_mutex)
	},	                           
#endif
	
#ifdef RT_USING_EVENT
	/* ��ʼ����������  -  �¼� */
	{
		RT_Object_Class_Event,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Event),
		sizeof(struct rt_event)
	},                          
#endif
	
#ifdef RT_USING_MAILBOX
	/* ��ʼ����������  -  ���� */
	{
		RT_Object_Class_MailBox, 
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MailBox),
		sizeof(struct rt_mailbox)
	},                    
#endif
	
#ifdef RT_USING_MESSAGEQUEUE
	/* ��ʼ����������  -  ��Ϣ���� */
	{
		RT_Object_Class_MessageQueue,  
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MessageQueue),
		sizeof(struct rt_messagequeue)
	},
#endif
	
#ifdef RT_USING_MEMHEAP
	/* ��ʼ����������  -  �ڴ�� */
	{
		RT_Object_Class_MemHeap,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemHeap),
		sizeof(struct rt_memheap)
	},                        
#endif
	
#ifdef RT_USING_MEMPOOL
	/* ��ʼ����������  -  �ڴ�� */
	{
		RT_Object_Class_MemPool, 
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_MemPool),
		sizeof(struct rt_mempool)
	},
#endif
	
#ifdef RT_USING_DEVICE
	/* ��ʼ����������  -  �豸 */
	{
		RT_Object_Class_Device, 
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Device),
		sizeof(struct rt_device)
	},		
#endif
	
	/* ��ʼ����������  -  ��ʱ�� */
	/*
	{
		RT_Object_Class_Timer,  
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Timer),
		sizeof(struct rt_timer)
	},
	 */
	
#ifdef RT_USING_MODULE
	/* ��ʼ����������  -  ģ�� */
	{
		RT_Object_Class_Module,
		_OBJ_CONTAINER_LIST_INIT(RT_Object_Info_Module),
		sizeof(struct rt_module)
	},	                          
#endif
	
};



/* ��ȡָ�����Ͷ�����Ϣ */

struct rt_object_information *
rt_object_get_information(enum rt_object_class_type type)
{
	int index;
	
	for(index = 0; index < RT_Object_Info_Unknown; index ++)
	{
		if(rt_object_container[index].type == type)
			return &rt_object_container[index];
	}
	
	return RT_NULL;
}




/* �����ʼ������ */

void rt_object_init(struct rt_object       *object,
					enum rt_object_class_type type,
					const char               *name)
{
	register rt_base_t temp;
	struct rt_object_information *information;
	
	/* ��ȡ������Ϣ �����������ó������б�ͷָ�� */
	information = rt_object_get_information(type);

	/* ���ö�������Ϊ��̬ */
	object->type = type | RT_Object_Class_Static;
	
	/* �������� */
	rt_strncpy(object->name, name, RT_NAME_MAX);
	
	/* ���ж� */   /* �ٽ�α��� */
	temp = rt_hw_interrupt_disable();
	
	/* ��������뵽�����Ķ�Ӧ���б��� ��ͬ���͵Ķ������ڵ��б���һ�� */
	rt_list_insert_after(&(information->object_list), &(object->list));
	
	/* ʹ���ж� */
	rt_hw_interrupt_enable(temp);
						
}







