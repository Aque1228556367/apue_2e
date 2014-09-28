// 4.3 文件类型
// 程序清单 4-1 对每个命令行参数打印文件类型(P87)
// 注：下面几个功能测试宏，都包含在<sys/stat.h>下
#include "myerr.h"
#include "apue.h"

int main(int argc, char *argv[])
{
	int			i = 0;
	struct stat	buf;
	const char		*ptr = NULL;

	for (i = 1; i < argc; ++i)
	{
		printf("%s: ", argv[i]);
		// 这里特地使用了 lstat() 函数而非 stat() 函数,以便检测符号链接。
		// 若采用 stat() 函数则无法观察到符号链接 :

		// 如：./test /dev/cdrom
		// 使用 stat() 则输出 block special
		// 而 lstat() 则输出character special
		if (lstat(argv[i], &buf) < 0)
		{
			err_ret("lstat error");
			continue;
		}

		// 普通文件
		if (S_ISREG(buf.st_mode))
			ptr = "regular";
		// 目录文件
		else if (S_ISDIR(buf.st_mode))
			ptr = "directory";
		// 字符特殊文件（提供对设备不带缓冲的访问，每次访问以可变长度进行）
		else if (S_ISCHR(buf.st_mode))
			ptr = "character special";
		// 块特殊文件（提供对设备带缓冲的访问，每次访问以固定长度进行）
		// 注：系统中的设备要么是【字符特殊文件】要么是【块特殊文件】
		else if (S_ISBLK(buf.st_mode))
			ptr = "block special";
		// FIFO文件：用于进程间通信，也被称作“命名管道（named pipe）”
		else if (S_ISFIFO(buf.st_mode))
			ptr = "fifo";
		// 符号链接文件
		else if (S_ISLNK(buf.st_mode))
			ptr = "symbolic link";
		// 套接字文件
		// 注：为了在 Linux 上编译该程序，
		//    必须定义 _GNU_SOURCE，这样才能包括 S_ISSOCK 宏的定义
		else if (S_ISSOCK(buf.st_mode))
			ptr = "socket";
		else
			ptr = "** unknown mode **";
		printf("%s\n", ptr);
	}
	exit(0);
}
