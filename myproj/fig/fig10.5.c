// 10.6 可重入函数
// 程序清单 10-2 在信号处理程序中调用不可重入函数(P261)
#include "myerr.h"
#include "apue.h"
#include <pwd.h>

// alarm 函数设置计时器超时，产生 SIGALRM 信号
// getpwnam : 获取用户口令文件项(6.4节, P149)

// getpwnam 不是signal可重入函数，如果在signal中重复定义，则会导致不确定的行为
// 在Linux中，本程序会直接终止运行
static void my_alarm(int signo)
{
	struct passwd	*rootptr;

	printf("in signal handler\n");
	if ((rootptr = getpwnam("root")) == NULL)
			err_sys("getpwnam(root) error");
	alarm(1);
}

int main(void)
{
	struct passwd	*ptr = NULL;

	signal(SIGALRM, my_alarm);
	alarm(1);
	for ( ; ; )
	{
		if ((ptr = getpwnam("sar")) == NULL)
			err_sys("getpwnam error");
		if (strcmp(ptr->pw_name, "sar") != 0)
			printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
	}
}
