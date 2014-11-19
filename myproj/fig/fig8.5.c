// 8.6 wait 和 waitpid 函数
// 程序清单 8-3 打印 exit 状态的说明（P194）
// 此示例即 prexit.c 的内容

// 产生中断的信号值对应的信号枚举
// WEXITSTATUS(status)
// WTERMSIG(status)
// WCOREDUMP(status)
// WSTOPSIG(status)
// 可通过 signum.h 查看
// 如，信号值6对应枚举SIGABRT

#include "myerr.h"
#include "apue.h"
#include <sys/wait.h>


void pr_exit(int status)
{
	if (WIFEXITED(status))
	{
		printf("normal termination, exit status = %d\n", WEXITSTATUS(status));
	}
	else if (WIFSIGNALED(status))
	{
		printf("abnormal termination, signal number = %d%s\n",
				WTERMSIG(status),
#ifdef	WCOREDUMP
				WCOREDUMP(status) ? " (core file generated)" : "");
#else
				"");
#endif
	}
	else if (WIFSTOPPED(status))
	{
		printf("child stopped, signal number = %d\n", WSTOPSIG(status));
	}
}
