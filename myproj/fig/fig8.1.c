// 8.3 fork 函数
// 程序清单 8-1 fork 函数示例（P187）
#include "myerr.h"
#include "apue.h"

int		glob = 6;		/* external variable in initialized data */
char	buf[] = "a write to stdout\n";

int main(void)
{
	int		var;		/* automatic variable on the stack */
	pid_t	pid;

	pid_t tFatherPID = getpid();
	printf("Father pid : %d\n", tFatherPID);

	var = 88;
	if (write(STDOUT_FILENO, buf, sizeof(buf)-1) != sizeof(buf)-1)
		err_sys("write error\n");

	printf("before fork\n");	/* we don't flush stdout */
	if (( pid = fork() ) < 0)
	{
		err_sys("fork error\n");
	}
	else if (pid == 0)
	{
		printf("The Child Process return Itself pid : %d\n", pid);
		glob++;					/* modify variables */
		var++;
	}
	else
	{
		printf("The Father Process return the Child pid : %d\n", pid);
		sleep(5);				/* parent */
		printf("The Father Process Has been Awaken .\n");
	}

	printf("pid = %d, glob = %d, var = %d\n", getpid(), glob, var);
	exit(0);
}
