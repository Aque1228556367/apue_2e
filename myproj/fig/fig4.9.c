// 4.8 umask 函数
// 程序清单 4-3 umask 函数实例
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int main(void)
{
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		err_sys("creat error for foo");

	// 修改当前进程的 umask 并不会对外层调用这个进程的 shell 的 umask 产生任何影响
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
		err_sys("creat error for bar");

	exit(0);
}
