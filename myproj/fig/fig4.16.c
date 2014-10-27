// 4.15 link、unlink、remove 和 rename 函数
// 程序清单 4-5 打开一个文件，然后 unlink 它(P104)
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

int main(void)
{
	if (open("tempfile", O_RDWR) < 0)
		err_sys("open error\n");
	if (unlink("tempfile") < 0)
		err_sys("unlink error\n");

	printf("file unlinked\n");
	sleep(15);
	printf("done\n");
	exit(0);
}
