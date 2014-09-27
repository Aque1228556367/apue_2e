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

	// 取得 argv[1] 对应文件的文件状态标志位
	int val = fcntl(atoi(argv[1]), F_GETFL, 0);
	if (val < 0)
		err_sys("fcntl error for fd %d", atoi(argv[1]));

	// O_ACCMODE : 操作时，用于取出 val 的低2位
	// 注意：O_RDONLY、O_WRONLY、O_RDWR 三者具有互斥性，三者的标志位不能包含在一起
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

	// 检测 val 是否包含“每次写时追加”的标志位
	if (val & O_APPEND)
		printf(", append");

	// 检测 val 是否包含“非阻塞模式”的标志位
	if (val & O_NONBLOCK)
		printf(", nonblocking");

// 系统中定义了 O_SYNC : 等待写完成（数据和属性）
#if defined(O_SYNC)
	if (val & O_SYNC)
		printf(", synchronous writes");
#endif

// 系统中定义了 O_FSYNC : 等待写完成（仅在 Mac 和 FreeBSD 中定义）
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
