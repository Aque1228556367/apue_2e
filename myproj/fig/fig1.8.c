// 1.7 出错处理
// 程序清单 1-6 例示 strerror 和 perror（P25）
#include "myerr.h"
#include "apue.h"
#include <errno.h>

int main(int argc, char *argv[])
{
	fprintf(stderr, "EACCES: %s\n", strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}
