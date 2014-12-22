// 10.10 alarm 和 pause 函数
// 程序清单 10-6 在一个捕捉其他信号的程序中调用sleep2(P268)
// #include "myerr.h"
#include "apue.h"

unsigned int	sleep2(unsigned int);
static void		sig_int(int);

int main(void)
{
	unsigned int	unslept;

	if (signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error");

	unslept = sleep2(5);

	// 问题：为什么这里不能用gdb跟到这里，而是直接退出？
	printf("sleep2 returned: %u\n", unslept);
	exit(0);
}

static void sig_int(int signo)
{
	int				i, j;
	volatile int	k;

	/*
	 * Tune these loops to run for more than 5 seconds
	 * on whatever system this test program is run.
	 */
	printf("\nsig_int starting\n");
	for (i = 0; i < 300000; i++)
		for (j = 0; j < 4000; j++)
			k += i * j;
	printf("sig_int finished\n");
}
