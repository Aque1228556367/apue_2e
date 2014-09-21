// 2.5.5 不确定的运行时限制
// 1. 路径名
// 程序清单 2-3 为路径名动态地分配空间(P53)
#include "myerr.h"
#include "apue.h"
#include <errno.h>
#include <limits.h>

#ifdef	PATH_MAX
static int	pathmax = PATH_MAX;
#else
static int	pathmax = 0;
#endif

#define SUSV3	200112L

static long	posix_version = 0;

/* If PATH_MAX is indeterminate, no guarantee this is adequate */
#define	PATH_MAX_GUESS	1024

char * path_alloc(int *sizep) /* also return allocated size, if nonnull */
{
	char	*ptr = NULL;
	int	size;

	if (posix_version == 0)
		posix_version = sysconf(_SC_VERSION);

	if (pathmax == 0)
	{	/* first time through */
		errno = 0;
		if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
		{
			if (errno == 0)
				pathmax = PATH_MAX_GUESS;	/* it's indeterminate */
			else
				err_sys("pathconf error for _PC_PATH_MAX");
		}
		else
		{
			++pathmax;		/* add one since it's relative to root */
		}
	}

	if (posix_version < SUSV3)
		size = pathmax + 1;
	else
		size = pathmax;

	ptr = (char*)malloc(size);
	if (ptr == NULL)
		err_sys("malloc error for pathname");

	if (sizep != NULL)
		*sizep = size;

	return(ptr);
}

int main()
{
	return 0;
}
