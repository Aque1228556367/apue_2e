// 8.9 竞争条件
// 程序清单 8-6 具有竞争条件的程序(P200)

// 疑问：
// 通过观察，发现 fig8.12.c 和 fig8.13.c 实际多次运行结果后，
// 都有可能出现输出错位的情况，而不是像书中所说那样的后者输出稳定

#include "myerr.h"
#include "apue.h"

static void charatatime(char *);

int main(void)
{
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{
		charatatime("output from child\n");
	}
	else
	{
		charatatime("output from parent\n");
	}
	exit(0);
}

static void charatatime(char *str)
{
	char *ptr = NULL;
	int	c = 0;

	setbuf(stdout, NULL);			/* set unbuffered */
	for (ptr = str; (c = *ptr++) != 0; )
		putc(c, stdout);
}

// 可通过下列脚本，更好的观察每次输出结果：
/*
for (( i=0;i<5;++i ));
do
        ./test
done
*/
