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