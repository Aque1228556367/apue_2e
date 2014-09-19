// 1.6 程序和进程
// 程序清单 1-4 打印进程ID（P22）
#include "myerr.h"
#include "apue.h"

int main(void)
{
	printf("hello world from process ID %d\n", getpid());
	exit(0);
}
