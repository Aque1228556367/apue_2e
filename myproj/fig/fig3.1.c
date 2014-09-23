// 3.6 lseek 函数
// 程序清单 3-1 测试能否对标准输入设置偏移量(P65)
#include "myerr.h"
#include "apue.h"

int main(void)
{
	// lseek (int fields, off_t offset, int whence)
	// 若 whence 是 SEEK_SET，则将该文件的偏移量设置为据文件开始处 offset 个字节
	// 若 whence 是 SEEK_CUR，则将该文件的偏移量设置其当前值加 offset，offset 可为正或负
	// 若 whence 是 SEEK_END，则将该文件的偏移量设置为文件长度加 offset，offset 可为正或负
	if (lseek(STDIN_FILENO, 0, SEEK_CUR) == -1)
		printf("cannot seek\n");
	else
		printf("seek OK\n");

	exit(0);
}

// 思考：
// $ ./test </etc/motd
// seek ok
// $ cat < /etc/motd |./test
// cannot seek
// ./test /var/spool/cron/FIFO
// cannot seek

// 为什么会有这种输出结果？
// 注：“<”表示将stdin重定向到某文件，即：从文件读入某文件
// 等价于 cat < /etc/motd
// cat /etc/motd  和  cat < /etc/motd  结果是一样的


// 参考：
// http://www.cnblogs.com/lovemo1314/archive/2011/07/13/2105472.html

//command > filename 　　　　　把标准输出重定向到一个新文件中
//command >> filename 　　　　　把标准输出重定向到一个文件中(追加)
//command 1 > fielname 　　　　　把标准输出重定向到一个文件中
//command > filename 2>&1 　　　把标准输出和标准错误一起重定向到一个文件中
//command 2 > filename 　　　　把标准错误重定向到一个文件中
//command 2 >> filename 　　　　把标准输出重定向到一个文件中(追加)
//command >> filename 2>&1 　　把标准输出和标准错误一起重定向到一个文件中(追加)
//command < filename >filename2 　　把command命令以filename文件作为标准输入，以filename2文件作为标准输出
//command < filename 　　　把command命令以filename文件作为标准输入
//command << delimiter 　　把从标准输入中读入，直至遇到delimiter分界符
//command <&m 　　　把文件描述符m作为标准输入
//command >&m 　　　把标准输出重定向到文件描述符m中
//command <&- 　　　把关闭标准输入

