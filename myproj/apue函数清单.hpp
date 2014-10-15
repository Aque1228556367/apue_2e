// Note : These notes use "gb2312/gbk" code-style and Unix code-style, 
// if it show within messy code, Please Use UltraEdit/UEStudio transformate it .
// if it show within "^M"( Ctrl + V, Ctrl + M ), Please Use "dos2unix" transformate it .

// 1.4 �ļ���Ŀ¼(fig1.3)

// define in glibc src( for Unix )
struct __dirstream
{
	int fd;						/* File descriptor.  */

	char *data;               /* Directory block.  Ŀ¼�� */
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
    __ino_t d_ino;			/* inode number �����ڵ�� */
    __off_t d_off;				/* offset to this dirent ��Ŀ¼�ļ��е�ƫ�� */
#else
    __ino64_t d_ino;
    __off64_t d_off;
#endif
    unsigned short int d_reclen;			/* length of this d_name �ļ����� */
    unsigned char d_type;					/* the type of d_name �ļ����� */
    char d_name[256];							/* file name (null-terminated) �ļ������255�ַ� */
    													/* We must not include limits.h! */
};

// ��Ŀ¼���
DIR* opendir(const char* dirname);

// ��һ��Ŀ¼
struct dirent* readdir(DIR* dirp);

// �ر�Ŀ¼���(�رճɹ��򷵻�0��ʧ�ܷ���-1)
int closedir(DIR* dirp);


// 1.5 ��������(fig1.4, fig1.5)

// Unix C :
// �ɹ����ض�ȡ���ֽ�����������-1������errno������ڵ�read֮ǰ�ѵ����ļ�ĩβ�������read����0
ssize_t read(int filedes, void* buf, unsigned int nbyte);
// ������д���Ѵ򿪵��ļ���
ssize_t write (int fd, const void * buf, size_t count);

// ANSI C :
// ������ȡ�ַ�.�˺�����ISO C����Ϊһ���꣬��������ʱ���ܽ�����Ϊ����ָ�봫
// #define getc(_fp) _IO_getc (_fp)
int getc(FILE *stream);

//////////////////////////////////////////////////////////////////////////
// Name : 	ferror
// Type :	Linux C
// Note :	����ļ����Ĵ���
// ���һ�ַ���ָ������.�˺�����ISO C����Ϊһ���꣬��������ʱ���ܽ�����Ϊ����ָ�봫
// #define putc(_ch, _fp) _IO_putc (_ch, _fp)
int fputc(int ch,FILE*fp);

//////////////////////////////////////////////////////////////////////////
// Name : 	ferror
// Type :	Linux C
// Note :	����ļ����Ĵ���

// �ڵ��ø������������������ putc.getc.fread.fwrite�ȣ�ʱ��
// ������ִ��󣬳��˺�������ֵ������ӳ�⣬��������ferror������顣
// ����һ�������ʽΪ ferror(fp)��
// ���ferror����ֵΪ0���٣�����ʾδ����
// �������һ������ֵ����ʾ����
// Ӧ��ע�⣬��ͬһ���ļ� ÿһ�ε����������������������һ���µ�ferror�� ��ֵ��
// ��ˣ�Ӧ���ڵ���һ��������������������� ��ferror������ֵ��������Ϣ�ᶪʧ��
// ��ִ��fopen����ʱ��ferror�����ĳ�ʼֵ�Զ���Ϊ0��
int ferror (FILE *__stream);


// 1.6 ����ͽ���(fig1.6, fig1.7)
//////////////////////////////////////////////////////////////////////////
// Name : 	getpid
// Type :	ANSI C
// Note :	ȡ�ý���ʶ����

// Windows
// Locate : process.h
// Define : 
_CRT_NONSTDC_DEPRECATE(_getpid) _CRTIMP int __cdecl getpid(void);
 
// CentOS 5.8
// Locate : /usr/include/unistd.h
// Define :	
extern __pid_t getpid (void) __THROW;

// Ubuntu 12.04	���� locate : 
// Locate : 
// Define :	

//////////////////////////////////////////////////////////////////////////

// 1.7 ������
