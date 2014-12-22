// 10.10 alarm 和 pause 函数
// 程序清单 10-5 sleep的另一个(不完整)实现(P267)
#include "myerr.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf	env_alrm;

static void sig_alrm(int signo)
{
	longjmp(env_alrm, 1);
}

unsigned int sleep2(unsigned int nsecs)
{
	if (signal(SIGALRM, sig_alrm) == SIG_ERR)
		return(nsecs);

	if (setjmp(env_alrm) == 0)
	{
		alarm(nsecs);		/* start the timer */
		pause();			/* next caught signal wakes us up */
	}
	printf("exit sleep2 function ...\n");
	return(alarm(0));		/* turn off timer, return unslept time */
}
