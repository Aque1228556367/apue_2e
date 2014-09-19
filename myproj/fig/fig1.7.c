// 1.6 程序和进程
// 程序清单 1-5 从标准输入读命令并执行（P23）
// ubuntu 默认情况下你在gdb中使用attach id是权限不够的，所以你需要：sudo chmod +s /usr/bin/gdb
#include "myerr.h"
#include "apue.h"
#include <sys/wait.h>

int main(void)
{
	char	buf[MAXLINE];	/* from apue.h */
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		pid_t pid = fork();
		printf("New Process : %d", pid);
		if (pid < 0)
		{
			err_sys("fork error");
		}
		else if (pid == 0)
		{	/* child */
			// 为便于调试子进程，需要在这停留一段时间，以便打开终端有足够的attach时间
			sleep(60);
			printf("Exec Child Process");
			execlp(buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}
