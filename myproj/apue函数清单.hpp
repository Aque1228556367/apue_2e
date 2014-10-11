// Note : These notes use "gb2312/gbk" code-style and Unix code-style, 
// if it show within messy code, Please Use UltraEdit/UEStudio transformate it .
// if it show within "^M"( Ctrl + V, Ctrl + M ), Please Use "dos2unix" transformate it .

// 1.4 文件和目录(fig1.3)

// define in glibc src( for Unix )
struct __dirstream
{
	int fd;						/* File descriptor.  */

	char *data;               /* Directory block.  目录块 */
	size_t allocation;       /* Space allocated for the block.  */
	size_t size;                /* Total valid data in the block.  */
	size_t offset;             /* Current offset into the block.  */

	off_t filepos;             /* Position of next entry to read.  */

	__libc_lock_define (, lock) /* Mutex lock for this structure.  */
};

//define in <dirent.h>
struct dirent
{
#ifndef __USE_FILE_OFFSET64
    __ino_t d_ino;			/* inode number 索引节点号 */
    __off_t d_off;				/* offset to this dirent 在目录文件中的偏移 */
#else
    __ino64_t d_ino;
    __off64_t d_off;
#endif
    unsigned short int d_reclen;			/* length of this d_name 文件名长 */
    unsigned char d_type;					/* the type of d_name 文件类型 */
    char d_name[256];							/* file name (null-terminated) 文件名，最长255字符 */
    													/* We must not include limits.h! */
};

// 打开目录句柄
DIR* opendir(const char* dirname);

// 读一个目录
struct dirent* readdir(DIR* dirp);

// 关闭目录句柄(关闭成功则返回0，失败返回-1)
int closedir(DIR* dirp);


// 1.5 输入和输出(fig1.4, fig1.5)

// Unix C :
// 成功返回读取的字节数，出错返回-1并设置errno，如果在调read之前已到达文件末尾，则这次read返回0
ssize_t read(int filedes, void* buf, unsigned int nbyte);
// 将数据写入已打开的文件内
ssize_t write (int fd, const void * buf, size_t count);

// ANSI C :
// 从流中取字符.此函数被ISO C声明为一个宏，所以在用时不能将其做为函数指针传
// #define getc(_fp) _IO_getc (_fp)
int getc(FILE *stream);
// 输出一字符到指定流中.此函数被ISO C声明为一个宏，所以在用时不能将其做为函数指针传
// #define putc(_ch, _fp) _IO_putc (_ch, _fp)
int fputc(int ch,FILE*fp);

// 在调用各种输入输出函数（如 putc.getc.fread.fwrite等）时，
// 如果出现错误，除了函数返回值有所反映外，还可以用ferror函数检查。
// 它的一般调用形式为 ferror(fp)；
// 如果ferror返回值为0（假），表示未出错。
// 如果返回一个非零值，表示出错。
// 应该注意，对同一个文件 每一次调用输入输出函数，均产生一个新的ferror函 数值，
// 因此，应当在调用一个输入输出函数后立即检 查ferror函数的值，否则信息会丢失。
// 在执行fopen函数时，ferror函数的初始值自动置为0。
int ferror (FILE *__stream);
