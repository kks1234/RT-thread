#ifndef __RT_SERVICE_H__
#define __RT_SERVICE_H__


/* rt_list_entry 宏定义 */
#define rt_container_of(ptr, type, member)  \
	((type*)((char*)(ptr) - (unsigned long)(&((type*)(0))->member)))
		
#define rt_list_entry(node, type, member)  \
	rt_container_of(node, type, member)


/*
*************************************************************************
*                           双向链表操作相关函数
*************************************************************************
*/

/* 初始化链表节点 */
rt_inline void rt_list_init(rt_list_t *l)
{
	l->next = l->prev = l;
}

/* 在双向链表头部插入一个节点 */
rt_inline void rt_list_insert_after(rt_list_t *l , rt_list_t *n)
{
	l->next->prev = n;
	n->next = l->next;
	l->next = n;
	n->prev = l;
}

/* 在双向链表尾部插入一个节点 */
rt_inline void rt_list_insert_before(rt_list_t *l , rt_list_t *n)
{
	l->prev->next = n;
	n->prev = l->prev;
	n->next = l;
	l->prev = n;
}

/* 从双向链表删除一个节点 */
rt_inline void rt_list_remove(rt_list_t *n)
{
	n->next->prev = n->prev;
	n->prev->next = n->next;
	/*free(n);*/
	n->next = n->prev = n;
}





#endif  /* __RT_SERVICE_H__ */


