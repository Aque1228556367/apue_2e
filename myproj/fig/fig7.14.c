// 7.10 setjmp 和 longjmp 函数
// 程序清单 7-7 自动变量的不正确使用(P178)
#include "myerr.h"
#include <stdio.h>

#define	DATAFILE "datafile"

FILE* open_data(void)
{
	FILE	*fp;
	char	databuf[BUFSIZ];  /* setvbuf makes this the stdio buffer */

	if ((fp = fopen(DATAFILE, "r")) == NULL)
		return(NULL);
	if (setvbuf(fp, databuf, _IOLBF, BUFSIZ) != 0)
		return(NULL);
	return(fp);		/* error */
}
