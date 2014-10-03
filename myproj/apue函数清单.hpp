// 1.4 文件和目录

// 打开目录句柄
DIR* opendir(const char* dirname);

// 读一个目录
struct dirent* readdir(DIR* dirp);

// 关闭目录句柄
closedir(DIR* dirp);


// 1.5 输入和输出

// 
read(int filedes, void* buf, unsigned int nbyte); 