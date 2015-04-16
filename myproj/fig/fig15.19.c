// 15.4 协同进程
// 程序清单 15-10 对两个数求和的过滤程序，使用标准I/O(P425)
// 作为 程序清单 15-9（fig15.18.c）的过滤程序，命名为 add3
#include "myerr.h"
#include "apue.h"

int main(void)
{
	int		int1, int2;
	char	line[MAXLINE];

	// 这些代码使得当有一行可用时，fgets 就返回，并使得当输出一换行符时，printf 立即执行 flush 操作
	// 对 setvbuf 进行的这些显式调用使得程序 15-10 能正常工作
	// •_IOLBF（行缓冲）：每次从流读入一行数据或向流写入数据。如：stdin, stdout
	if ( setvbuf(stdin, NULL, _IOLBF, 0) != 0 )
		err_sys("setvbuf error");
	if ( setvbuf(stdout, NULL, _IOLBF, 0) != 0 )
		err_sys("setvbuf error");

	// 标准输入是个管道，而标准I/O库系统默认是全缓冲的，如果不进行 setvbuf 的设置，
	// 当下面 ssanf 读取而发生阻塞时，程序清单 15-9 从管道读时也发生阻塞
	while (fgets(line, MAXLINE, stdin) != NULL)
	{
		// 必须读入两个字符
		if (sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			if (printf("%d\n", int1 + int2) == EOF)
				err_sys("printf error");
		}
		else
		{
			if (printf("invalid args\n") == EOF)
				err_sys("printf error");
		}
	}
	exit(0);
}
