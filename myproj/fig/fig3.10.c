// 3.6 fcntl 函数
// 程序清单 3-4 对于指定的文件描述符打印文件标识(P78)
// fcntl 函数可以改变已打开的文件的性质
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <descriptor#>");

	int val = fcntl(atoi(argv[1]), F_GETFL, 0);
	if (val < 0)
		err_sys("fcntl error for fd %d", atoi(argv[1]));

	switch (val & O_ACCMODE)
	{
	case O_RDONLY:
		printf("read only");
		break;

	case O_WRONLY:
		printf("write only");
		break;

	case O_RDWR:
		printf("read write");
		break;

	default:
		err_dump("unknown access mode");
	}

	if (val & O_APPEND)
		printf(", append");
	if (val & O_NONBLOCK)
		printf(", nonblocking");

#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writes");
#endif
#if !defined(_POSIX_C_SOURCE) && defined(O_FSYNC)
	if (val & O_FSYNC)
		printf(", synchronous writes");
#endif
	putchar('\n');
	exit(0);
}

// 教材中用到的例子：
// ./test 1 > temp.foo
// ./test 2 2>>temp.foo
// ./test 5 5<>temp.foo
