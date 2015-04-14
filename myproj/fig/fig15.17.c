// 15.4 协同进程
// 程序清单 15-8 对两个数求和的简单过滤程序(P423)
// 作为 程序清单 15-9（fig15.18.c）的过滤程序，命名为 add2
#include "myerr.h"
#include "apue.h"

int main(void)
{
	int		n, int1, int2;
	char	line[MAXLINE];

	while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
	{
		line[n] = 0;		/* null terminate */
		if (sscanf(line, "%d%d", &int1, &int2) == 2)
		{
			sprintf(line, "%d\n", int1 + int2);
			n = strlen(line);
			if (write(STDOUT_FILENO, line, n) != n)
				err_sys("write error");
		}
		else
		{
			if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
				err_sys("write error");
		}
	}
	exit(0);
}
