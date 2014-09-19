// 2.5.4 sysconf、pathconf 和 fpathconf 函数（P46）
// 程序清单 2-2 打印所有可能的 sysconf 和 pathconf 值(P50)
// 注意：高版本编译时可能会出错，要将 pr_sysconf 和 pr_pathconf 两函数的参数类型的
// char* 改为 const char*
#include "myerr.h"
#include "apue.h"
#include <errno.h>
#include <limits.h>

static void	pr_sysconf(const char *, int);
static void	pr_pathconf(const char *, const char *, int);

int main(int argc, char *argv[])
{
	if (argc != 2)
		err_quit("usage: a.out <dirname>");

#ifdef ARG_MAX
	printf("ARG_MAX defined to be %d\n", ARG_MAX+0);
#else
	printf("no symbol for ARG_MAX\n");
#endif
#ifdef _SC_ARG_MAX
	pr_sysconf("ARG_MAX =", _SC_ARG_MAX);
#else
	printf("no symbol for _SC_ARG_MAX\n");
#endif

/* similar processing for all the rest of the sysconf symbols... */

#ifdef MAX_CANON
	printf("MAX_CANON defined to be %d\n", MAX_CANON+0);
#else
	printf("no symbol for MAX_CANON\n");
#endif
#ifdef _PC_MAX_CANON
	pr_pathconf("MAX_CANON =", argv[1], _PC_MAX_CANON);
#else
	printf("no symbol for _PC_MAX_CANON\n");
#endif

/* similar processing for all the rest of the pathconf symbols... */

	exit(0);
}

static void pr_sysconf(const char *mesg, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = sysconf(name)) < 0)
	{
		if (errno != 0)
		{
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("sysconf error");
		}
		else
		{
			fputs(" (no limit)\n", stdout);
		}
	}
	else
	{
		printf(" %ld\n", val);
	}
}

static void pr_pathconf(const char *mesg, const char *path, int name)
{
	long	val;

	fputs(mesg, stdout);
	errno = 0;
	if ((val = pathconf(path, name)) < 0)
	{
		if (errno != 0)
		{
			if (errno == EINVAL)
				fputs(" (not supported)\n", stdout);
			else
				err_sys("pathconf error, path = %s", path);
		}
		else
		{
			fputs(" (no limit)\n", stdout);
		}
	}
	else
	{
		printf(" %ld\n", val);
	}
}
