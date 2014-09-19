// 1.8 用户标识
// 程序清单 1-7 打印用户ID和组ID（P27）
#include "myerr.h"
#include "apue.h"

int main(void)
{
	printf("uid = %d, gid = %d\n", getuid(), getgid());
	exit(0);
}
