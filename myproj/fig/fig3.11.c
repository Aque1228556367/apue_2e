// 3.6 fcntl 函数
// 程序清单 3-5 对一个文件描述符打开一个或多个文件状态标志(P79)
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

void set_fl(int fd, int flags) /* flags are file status flags to turn on */
{
	int		val;

	if ((val = fcntl(fd, F_GETFL, 0)) < 0)
		err_sys("fcntl F_GETFL error");

	val |= flags;		/* turn on flags */

	if (fcntl(fd, F_SETFL, val) < 0)
		err_sys("fcntl F_SETFL error");
}
