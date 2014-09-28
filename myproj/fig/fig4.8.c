// 4.7 access 函数
// 程序清单 4-2 access 函数实例(P92)
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <pathname>");
	if (access(argv[1], R_OK) < 0)
		err_ret("access error for %s\n", argv[1]);
	else
		printf("read access OK\n");
	if (open(argv[1], O_RDONLY) < 0)
		err_ret("open error for %s\n", argv[1]);
	else
		printf("open for reading OK\n");
	exit(0);
}
