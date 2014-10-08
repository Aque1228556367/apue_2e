// 1.5 输入和输出
// 程序清单 1-3 用标准I/O将标准输入复制到标准输出
#include "myerr.h"
#include "apue.h"

int main(void)
{
	int	c;

	while ((c = getc(stdin)) != EOF)
		if (putc(c, stdout) == EOF)
			err_sys("output error");

	if (ferror(stdin))
		err_sys("input error");

	exit(0);
}
