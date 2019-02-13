#include <rtthread.h>
#include <rthw.h>






/* 复制n长度的字符串 */

char *rt_strncpy(char *dst, const char *src, rt_ubase_t n)
{
	if(n != 0)
	{
		char *d = dst;
		const char *s = src;
		
		do {
			if((*d++ = *s++) == 0)
			{
				/* NUL pad the remaining n-1 bytes */
				while(--n != 0)
					*d++ = 0;
				break;
			}
		}while(--n != 0);
			
	}
	return (dst);
}















