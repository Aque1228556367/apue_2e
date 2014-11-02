// 参数说明：
// int fields —— 文件描述符
// 在UNIX、Linux的系统调用中，大量的系统调用都是依赖于文件描述符
// 在非UNIX/Linux操作系统上(如Windows NT)，无法基于这一概念进行编程
// 范围： 0 到 OPEN_MAX
// 含义：是由无符号整数表示的句柄，进程使用它来标识打开的文件。
//    文件描述符与包括相关信息（如文件的打开模式、文件的位置类型、文件的初始类型等）
// 的文件对象相关联，这些信息被称作文件的上下文。

// 1.4 (P25)
#include <string.h>
char* strerror(int errnum);

#include <stdio.h>
void perror(const char* msg);

// 2.5(P47) Unix OS Limit
#include <unistd.h>	// Only for Unix
// 若成功则返回相应值，若失败返回-1
// See in fig2.15, fig2.16
long sysconf(int name);
long pathconf(const char* pathname, int name);
long fpathof(int fields, int name);

// 3.3(P62) 打开和创建文件
// 若成功则返回文件描述符，失败返回-1
#include <fcntl.h>
// oflag : [O_RDONLY, O_WRONLY, O_RDWR] only one + other "O_***" sign
// 若 oflag为 O_CREAT, 需要使用第三个参数 mode(4.5节), 表示该文件的用户权限
int open(const char* pathname, int oflag, ... /*mode_t mode*/);

// 3.4(P64) 创建一个文件并以只写的方式打开。如果原来该文件存在，会将这个文件的长度截短为0
// 若成功则返回为“只写”打开的文件描述符，失败返回-1
#include <fcntl.h>
// See in fig3.2
// 等效于 open( O_WRONLY | O_CREAT | O_TRUNC, mode )
// 由于创建文件后是以只写的方式打开，因此局限性比较大, 现一般使用
// open( O_RDWR | O_CREAT | O_TRUNC, mode ) 代替
int creat(const char* pathname, mode_t mode);

// 3.5(P64) 关闭一个关联该文件描述符的文件
// 若成功则返回0，失败返回-1
#include<unistd.h>	// Only for Unix
int close(int fields);

// 3.6(P64) 显式的为一个打开的文件设置其偏移量
// 若成功则返回新的文件偏移量，出错返回-1
#include <unistd.h>	// Only for Unix
// See in fig3.1, fig3.2
// whence : SEEK_SET, SEEK_CUR or SEEK_END
off_t lseek(int fields, off_t offset, int whence);

// 3.7(P67) and 3.8(P68) 从打开文件中读/写数据
// See in fig1.4
#include <unistd.h>	// Only for Unix
// 若成功则返回读到的字节数，若已到达文件尾则返回0，出错返回-1
// See in fig3.4
ssize_t read(int fields, void* buf, size_t bytes);
// 若成功则返回已经写入的字节数，出错返回-1
// See in fig3.2, fig3.4
ssize_t write(int fields, const void* buf, size_t bytes);

// 3.11(P73) 原子读写, 返回值和 read/write 一致
#include <unistd.h>	// Only for Unix
ssize_t pread(int fields, void* buf, size_t bytes, off_t offset);
ssize_t pwrite(int fields, const void* buf, size_t bytes, off_t offset);

// 3.12(P74) 复制一个现存的文件描述符 fields
// 若成功则返回新的文件描述符，失败返回-1
#include <unistd.h>	// Only for Unix
int dup(int fields);
int dup2(int fields, int fields2);

// 3.13(P75) 将缓存中的信息写入磁盘，保证文件和高速缓存内容一致
// 若成功则返回0，失败返回-1
#include <unistd.h>	// Only for Unix
int fsync(int fields);
int fdatasync(int fields);// Only for Linux
void sync(void);

// 3.14(P76) 改变已打开的文件性质 ☆☆☆☆☆
// 若成功则依赖 cmd，若失败则返回-1
#include <fcntl.h>
// See in fig3.10
int fcntl(int fields, int cmd /* , int args .. */);

// 3.15(P81) 其它对I/O通道进行管理的方法
#include <unistd.h>		/* System V */
#include <sys/ioctl.h>	/* BSD and Linux */
#include <stropts.h>	/* XSI Streams */
int ioctl(int fields, int request, ...);

// 4.2(P85) 文件的状态详细信息
/* 
 * 注：restrict，C语言中的一种类型限定符（Type Qualifiers），
 * 用于告诉编译器，对象已经被指针所引用，
 * 不能通过除该指针外所有其他直接或间接的方式修改该对象的内容。
 */
#include <sys/stat.h>
// See in fig4.12, fig4.21
int stat(const char* __restrict pathname, struct stat* __restrict buf);
int fstat(int fields, struct stat* buf);
// See in fig4.3, fig4.22
int lstat(const char* __restrict pathname, struct stat* __restrict buf);

// 4.7(P92) 权限控制
#include <unistd.h>		// Only for Unix
// See in fig4.8
int access(const char* pathname, int mode);

// 4.8(P93) 设置文件模式创建屏蔽字
#include <sys/stat.h>
// See in fig4.9
mode_t umask(mode_t cmask);

// 4.9(P95) 更改现有文件的访问权限
#include <sys/stat.h>
// See in fig4.12
int chmod(const char* pathname, mode_t mode);
int fchmod(int fields, mode_t mode);

// 4.11(P98) 更改文件的用户ID和组ID
#include <unistd.h>		// Only for Unix
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fields, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);

// 4.13(P100) 文件截短
#include <unistd.h>		// Only for Unix
int truncate(const char *pathname, off_t length);
int ftruncate(int fields, off_t length);

// 4.15(P103) 文件连接(硬连接)
#include <unistd.h>		// Only for Unix
int link(const char *existingpath, const char *newpath);
// See in fig4.16
int unlink(const char *pathname);

#include <stdio.h>
int remove(const char *pathname);
int rename(const char *oldname, const char * newname);

// 4.17(P108) 符号链接(软连接)
#include <unistd.h>		// Only for Unix
int symlink(const char *actualpath, const char *sympath);
ssize_t readlink(const char* __restrict pathname, char* __restrict buf, size_t bufsize);

// 4.19(P110) 文件的修改和访问时间
#include <utime.h>		// Only for Unix
// See in fig4.21
int utime(const char * pathname, const struct utimbuf* times);

struct utimbuf
{
	time_t actime;		/*access time*/
	time_t modtime;	/*modification time*/
};

// 4.20(P111) 创建/删除目录
#include <sys/stat.h>
int mkdir(const char* pathname, mode_t mode);

#include <unistd.h>		// Only for Unix
int rmdir(const char* pathname);

// 4.21(P112) 读目录
// See in fig1.3, fig4.22
#include <dirent.h>		// Only for Unix
DIR* opendir(const char* pathname);

struct dirent* readdir(DIR* dirp);

void rewinddir(DIR* dirp);
int closedir(DIR* dirp);

long telldir(DIR* dirp);	// Only for Unix XSI

void seekdir(DIR* dirp, long loc);// Only for Unix XSI

struct dirent
{
	ino_t d_ino;									/* i-node number */
	char d_name[NAME_MAX + 1];		/* null-terminated('\0') filename */
	/* ...... */
};

// 4.22(P116) 工作目录
#include <unistd.h>		// Only for Unix
int chdir(const char *pathname);
int fchdir(int fields);

char* getcwd(char* buf, size_t size);


// 5.2 流和 I/O 对象
// (P123)设置流的定向
#include <stdio.h>
#include <wchar.h>
// 若是宽字节定向返回值 > 0，若是宽字节定向返回值 < 0，未定向返回 0
// 若 mode < 0 fwide 将试图使指定的流是字节定向
// 若 mode > 0 fwide 将试图使指定的流是宽定向
int fwide(FILE *fp, int mode);

// 5.4(P124) 缓冲
#include <stdio.h>
int setbuf(FILE* __restrict fp, char* __restrict buf);
int setvbuf(FILE* __restrict fp, char* __restrict buf, int mode, size_t size);

// 5.5(P126) 打开流 关闭流
#include <stdio.h>
FILE* fopen(const char* __restrict pathname, const char* __restrict type);
FILE* freopen(const char* __restrict pathname, const char* __restrict type, FILE* __restrict fp);
FILE* fdopen(int fields, const char* type);

int fclose(FILE* fp);

// 5.6(P129) 读和写流
#include <stdio.h>
// See in fig1.5

// 若成功则返回下一个字符，若已到达文件尾或出错则返回EOF
int getc(FILE* fp);
int fgetc(FILE* fp);
int getchar(void);

// 若成功则返回c，若失败则返回EOF
int putc(int c, FILE* fp);
int fputc(int c, FILE* fp);
int putchar(int c);


// 区分到达文件尾还是出错：
int ferror(FILE* fp);
int feof(FILE* fp);

// 清除 ferror 和 feof 标志位
int clearerr(FILE* fp);


// 从流中读取数据后，再压回流中
int ungetc(int c, FILE* fp);

// 5.7(P130)
