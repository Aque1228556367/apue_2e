// 8.10 exec 函数
// 程序清单 8-9 回送所有命令行参数和所有环境字符串(P206)
// 此为 fig8.16.c 所需的 echoall 进程
#include "myerr.h"
#include "apue.h"

int main(int argc, char *argv[])
{
	int			i;
	char		**ptr;
	extern char	**environ;

	for (i = 0; i < argc; i++)		/* echo all command-line args */
		printf("argv[%d]: %s\n", i, argv[i]);

	for (ptr = environ; *ptr != 0; ptr++)	/* and all env strings */
		printf("%s\n", *ptr);

	exit(0);
}
