// 1.4 (P25)
#include <string.h>
char* strerror(int errnum);

#include <stdio.h>
void perror(const char* msg);


// 3.3(P62)
#include <fcntl.h>
int open(const char* pathname, int oflag, ... /*mode_t mode*/);

// 3.4(P64)
#include <fcntl.h>
int creat(const char* pathname, mode_t mode);

// 3.5(P64)
#include<unistd.h>	// Only for Unix
int close(int fields);

// 3.6(P64)
#include <unistd.h>	// Only for Unix
off_t lseek(int fields, off_t offset, int whence);

// 3.7(P67)
#include <unistd.h>	// Only for Unix
ssize_t read(int fields, void* buf, size_t bytes);

// 3.8(P68)
#include <unistd.h>	// Only for Unix
ssize_t write(int fields, const void* buf, size_t bytes);

// 3.11(P73) 原子读写
#include <unistd.h>	// Only for Unix
ssize_t pread(int fields, void* buf, size_t bytes, off_t offset);
ssize_t pwrite(int fields, const void* buf, size_t bytes, off_t offset);

// 3.12(P74) 复制一个现存的文件描述符 fields
#include <unistd.h>	// Only for Unix
int dup(int fields);
int dup2(int fields, int fields2);

// 3.13(P75) 将缓存中的信息写入磁盘，保证文件和高速缓存内容一致
#include <unistd.h>	// Only for Unix
int fsync(int fields);
int fdatasync(int fields);
void sync(void);

// 3.14(P76) 改变已打开的文件性质
#include <fcntl.h>
int fcntl(int fields, int cmd, .. , /* int arg */);

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
int stat(const char* restrict pathname, struct stat* restrict buf);
int fstat(int fields, struct stat* buf);
int lstat(const char* restrict pathname, struct stat* restrict buf);

// 4.7(P92) 权限控制
#include <unistd.h>		// Only for Unix
int access(const char* pathname, int mode);

// 4.8(P93) 设置文件模式创建屏蔽字
#include <sys/stat.h>
mode_t umask(mode_t cmask);

// 4.9(P95) 更改现有文件的访问权限
#include <sys/stat.h>
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
int unlink(const char *pathname);

#include <stdio.h>
int remove(const char *pathname);
int rename(const char *oldname, const char * newname);

// 4.17(P108) 符号链接(软连接)
#include <unistd.h>		// Only for Unix
int symlink(const char *actualpath, const char *sympath);
ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize);

// 4.19(P110) 文件的修改和访问时间
#include <utime.h>		// Only for Unix
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
	......
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
int setbuf(FILE* restrict fp, char* restrict buf);
int setvbuf(FILE* restrict fp, char* restrict buf, int mode, size_t size);

