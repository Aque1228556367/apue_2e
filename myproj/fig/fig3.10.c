// 3.6 fcntl 函数
// 程序清单 3-4 对于指定的文件描述符打印文件标识(P78)
// fcntl 函数可以改变已打开的文件的性质
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <descriptor#>\n");

	// 取得 argv[1] 对应文件的文件状态标志位
	int tFields = atoi(argv[1]);
	int val = fcntl(tFields, F_GETFL, 0);
	if (val < 0)
		err_sys("fcntl error for fd %d\n", atoi(argv[1]));

	switch(tFields)
	{
	case 0:
		printf("File Descriptor : %d is stdin\n", tFields);
		break;
	case 1:
		printf("File Descriptor : %d is stdout\n", tFields);
		break;
	case 2:
		printf("File Descriptor : %d is stderr\n", tFields);
		break;
	default:
		printf("Other unOS File Descriptor : %d\n", tFields);
		break;
	}
	// O_ACCMODE : 操作时，用于取出 val 的低2位
	// 注意：O_RDONLY、O_WRONLY、O_RDWR 三者具有互斥性，三者的标志位不能包含在一起
	switch (val & O_ACCMODE)
	{
	case O_RDONLY:
		printf("Get file status flags : read only");
		break;

	case O_WRONLY:
		printf("Get file status flags : write only");
		break;

	case O_RDWR:
		printf("Get file status flags : read write");
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
// ./test 0 < /dev/tty
// ./test 1 > temp.foo
// ./test 2 2>>temp.foo
// ./test 5 5<>temp.foo

// 注：1、2、5 都是文件描述符，数字1、2、3分别表示标准输入、标准输出和标准出错(P61, 3.2)，
// 此三个文件描述符为系统预留，其它皆为自定义文件描述符，最大不得超过 OPEN_MAX

// ./test 0 < /dev/tty 表示重定向终端到输入流，和 ./test 0 输出结果并无二致
// printf() 函数将格式化数据写到标准输出(P136)，> 命令会把所有 printf 的内容
// 重定向到 temp.foo 文件中, > 会覆盖之前的文件内容，而 >> 则可以在原来的内容上追加
// 5<>temp.foo 表示：为了读写 temp.foo，把 temp.foo 打开，并且将文件描述符5分配给它
// 并不会把输出流内容写到 temp.foo 文件上
// 所以文件描述符5的文件标志位是读写（以读写标志位模式打开的）

// <unistd.h>
/* Standard file descriptors.  */
// #define	STDIN_FILENO	0	/* Standard input. */
// #define	STDOUT_FILENO	1	/* Standard output.*/
// #define	STDERR_FILENO	2	/* Standard error output.*/

// 关于重定向和文件描述符，可参考：
// http://blog.csdn.net/runboying/article/details/7045797
// http://www1.huachu.com.cn/read/readbookinfo.asp?sectionid=1000006953

