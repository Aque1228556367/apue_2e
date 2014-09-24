// 3.6 lseek 函数
// 程序清单 3-2 创建一个具有空洞的文件(P66)
// 产生空洞文件的方法：使文件的偏移量大于文件的当前长度
#include "myerr.h"
#include "apue.h"
#include <fcntl.h>

char	buf1[] = "abcdefghij";
char	buf2[] = "ABCDEFGHIJ";

int main(void)
{
	int		fd;

	if ((fd = creat("file.hole", FILE_MODE)) < 0)
		err_sys("creat error");

	if (write(fd, buf1, 10) != 10)
		err_sys("buf1 write error");
	/* offset now = 10 */

	if (lseek(fd, 16384, SEEK_SET) == -1)
		err_sys("lseek error");
	/* offset now = 16384 */

	if (write(fd, buf2, 10) != 10)
		err_sys("buf2 write error");
	/* offset now = 16394 */

	exit(0);
}
// 注：(16384)Dec == (40000)Oct
// 输出结果：（-c 标识表示以字符方式打印文件内容）
// $ od -c file.hole 
//                     第一次write操作写入10个小写字母（文件偏移位置还在其实位置）
//                                               ↓
// 0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
// 0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
// *
// 0040000   A   B   C   D   E   F   G   H   I   J
// 0040012

//od(octal dump)
//功能说明：输出文件内容。
//补充说明：od指令会读取所给予的文件的内容，并将其内容以八进制字码呈现出来。
//          因为 od命令系统默认的显示方式是八进制，这也是该命令的名称由来（Octal Dump）
