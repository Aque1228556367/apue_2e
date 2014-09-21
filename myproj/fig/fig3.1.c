// 3.6 lseek 函数
// 程序清单 3-1 测试能否对标准输入设置偏移量(P65)
#include "myerr.h"
#include "apue.h"

int main(void)
{
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");

	exit(0);
}
