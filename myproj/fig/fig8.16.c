// 8.10 exec 函数
// 程序清单 8-8 exec 函数实例(P205)
// 所需的 echoall 进程为 fig8.16.c

// 疑问：总是提示执行echoall的权限不够( Permission denied )？
#include "myerr.h"
#include "apue.h"
#include <sys/wait.h>

char	*env_init[] = { "USER=unknown", "PATH=/tmp", NULL };

//const char* whole_path = "/home/sar/bin/echoall";
const char* whole_path = "/home/sunrise/apue_2e_svn/apue_2e/trunk/myproj/bin";

int main(void)
{
	printf( "Current process id : %d\n", getpid() );
	pid_t pid;

	if ((pid = fork()) < 0)
	{
		err_sys("fork error");
	}
	else if (pid == 0)
	{	/* specify pathname, specify environment */
		if (execle(whole_path,
				"echoall",
				"myarg1",
				"MY ARG2",
				(char *)0,
				env_init) < 0)
			err_sys("execle error");
		printf("\n");
	}

	if (waitpid(pid, NULL, 0) < 0)
		err_sys("wait error\n");

	if ((pid = fork()) < 0)
	{
		err_sys("fork error\n");
	}
	else if (pid == 0)
	{	/* specify filename, inherit environment */
		if (execlp("echoall", "echoall", "only 1 arg", (char *)0) < 0)
			err_sys("execlp error");
		printf("\n");
	}

	exit(0);
}
