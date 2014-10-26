// 3.3(P62)
#include <fcntl.h>
int open(const char* pathname, int oflag, ... /*mode_t mode*/);

#include <fcntl.h>
int creat(const char* pathname, mode_t mode);

#include<unistd.h>
int close(int fields);


