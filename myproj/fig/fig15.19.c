// 15.4 协同进程
// 程序清单 15-10 对两个数求和的过滤程序，使用标准I/O(P425)
// 作为 程序清单 15-9（fig15.18.c）的过滤程序，命名为 add2
#include "myerr.h"
#include "apue.h"

int main(void)
{
	int		int1, int2;
	char	line[MAXLINE];

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
