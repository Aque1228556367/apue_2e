// 1.4 �ļ���Ŀ¼

// ��Ŀ¼���
DIR* opendir(const char* dirname);

// ��һ��Ŀ¼
struct dirent* readdir(DIR* dirp);

// �ر�Ŀ¼���
closedir(DIR* dirp);


// 1.5 ��������

// 
read(int filedes, void* buf, unsigned int nbyte); 