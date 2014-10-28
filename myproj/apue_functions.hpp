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

// 3.11(P73) ԭ�Ӷ�д
#include <unistd.h>	// Only for Unix
ssize_t pread(int fields, void* buf, size_t bytes, off_t offset);
ssize_t pwrite(int fields, const void* buf, size_t bytes, off_t offset);

// 3.12(P74) ����һ���ִ���ļ������� fields
#include <unistd.h>	// Only for Unix
int dup(int fields);
int dup2(int fields, int fields2);

// 3.13(P75) �������е���Ϣд����̣���֤�ļ��͸��ٻ�������һ��
#include <unistd.h>	// Only for Unix
int fsync(int fields);
int fdatasync(int fields);
void sync(void);

// 3.14(P76) �ı��Ѵ򿪵��ļ�����
#include <fcntl.h>
int fcntl(int fields, int cmd, .. , /* int arg */);

// 3.15(P81) ������I/Oͨ�����й���ķ���
#include <unistd.h>		/* System V */
#include <sys/ioctl.h>	/* BSD and Linux */
#include <stropts.h>	/* XSI Streams */
int ioctl(int fields, int request, ...);

// 4.2(P85) �ļ���״̬��ϸ��Ϣ
/* 
 * ע��restrict��C�����е�һ�������޶�����Type Qualifiers����
 * ���ڸ��߱������������Ѿ���ָ�������ã�
 * ����ͨ������ָ������������ֱ�ӻ��ӵķ�ʽ�޸ĸö�������ݡ�
 */
#include <sys/stat.h>
int stat(const char* restrict pathname, struct stat* restrict buf);
int fstat(int fields, struct stat* buf);
int lstat(const char* restrict pathname, struct stat* restrict buf);

// 4.7(P92) Ȩ�޿���
#include <unistd.h>		// Only for Unix
int access(const char* pathname, int mode);

// 4.8(P93) �����ļ�ģʽ����������
#include <sys/stat.h>
mode_t umask(mode_t cmask);

// 4.9(P95) ���������ļ��ķ���Ȩ��
#include <sys/stat.h>
int chmod(const char* pathname, mode_t mode);
int fchmod(int fields, mode_t mode);

// 4.11(P98) �����ļ����û�ID����ID
#include <unistd.h>		// Only for Unix
int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fields, uid_t owner, gid_t group);
int lchown(const char *pathname, uid_t owner, gid_t group);

// 4.13(P100) �ļ��ض�
#include <unistd.h>		// Only for Unix
int truncate(const char *pathname, off_t length);
int ftruncate(int fields, off_t length);

// 4.15(P103) �ļ�����(Ӳ����)
#include <unistd.h>		// Only for Unix
int link(const char *existingpath, const char *newpath);
int unlink(const char *pathname);

#include <stdio.h>
int remove(const char *pathname);
int rename(const char *oldname, const char * newname);

// 4.17(P108) ��������(������)
#include <unistd.h>		// Only for Unix
int symlink(const char *actualpath, const char *sympath);
ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize);

// 4.19(P110) �ļ����޸ĺͷ���ʱ��
#include <utime.h>		// Only for Unix
int utime(const char * pathname, const struct utimbuf* times);

struct utimbuf
{
	time_t actime;		/*access time*/
	time_t modtime;	/*modification time*/
};

// 4.20(P111) ����/ɾ��Ŀ¼
#include <sys/stat.h>
int mkdir(const char* pathname, mode_t mode);

#include <unistd.h>		// Only for Unix
int rmdir(const char* pathname);

// 4.21(P112) ��Ŀ¼
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

// 4.22(P116) ����Ŀ¼
#include <unistd.h>		// Only for Unix
int chdir(const char *pathname);
int fchdir(int fields);

char* getcwd(char* buf, size_t size);


// 5.2 ���� I/O ����
// (P123)�������Ķ���
#include <stdio.h>
#include <wchar.h>
// ���ǿ��ֽڶ��򷵻�ֵ > 0�����ǿ��ֽڶ��򷵻�ֵ < 0��δ���򷵻� 0
// �� mode < 0 fwide ����ͼʹָ���������ֽڶ���
// �� mode > 0 fwide ����ͼʹָ�������ǿ���
int fwide(FILE *fp, int mode);

// 5.4(P124) ����
#include <stdio.h>
int setbuf(FILE* restrict fp, char* restrict buf);
int setvbuf(FILE* restrict fp, char* restrict buf, int mode, size_t size);

