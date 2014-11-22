// parent.c
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{        
	int fd = open("test.txt",O_RDWR|O_APPEND);

	if (fd == -1)
	{       
		printf("The file test.txt open failed ! The fd = %d\n",fd);
		execl( "/bin/touch", "touch", "test.txt", (char*)NULL );
		return 0;
	}
	else
	{       
		printf("The file test.txt open success ! The fd = %d\n", fd);
	}

	printf("fork!\n");


	// 系统默认 fcntl(fd, F_SETFD, 0) ，即用 execl 执行子进程时，
	// 不打开“执行时关闭”标识位 FD_CLOEXEC
	//fcntl(fd, F_SETFD, 1);
	//fcntl(fd, F_SETFD, 0);

	// 和 fcntl(fd, F_SETFD, 1) 等效，但这是标准写法，即用 FD_CLOEXEC 取代直接写1
	int tFlags = fcntl(fd, F_GETFD);
	fcntl(fd, F_SETFD, tFlags | FD_CLOEXEC );

	char *s="The Parent Process Writed !\n";

	pid_t pid = fork();
	// 如果想在 gdb 调试子进程，请在调试之前设置 follow-fork-mode：
	// set follow-fork-mode child
	// 但是如果设置调试子进程，则子进程结束后，无法继续调试父进程了
	if(pid == 0)										/* Child Process */
	{       
		printf("***** exec child *****\n");
		
		// execl("child", "./child", &fd, NULL);
		// 注意下面，子进程不用 exec 函数，而是改成直接写入处理
		// 此时文件描述符标识位 FD_CLOEXEC 不再起作用
		// 即使设置这个标识位，子进程一样可以写入
		char *s = "The Child Process Writed !\n";
		ssize_t writebytes = write(fd, (void *)s, strlen(s));
		if ( writebytes == -1 )
		{
			printf("The Child Process Write To fd : %d Failed !\n", fd);
		}       
		
		printf("**********************\n");
		// 注意这里结束子进程，但不要关闭文件描述符，否则父进程无法写入
		exit(0);
	}

	// 等待子进程执行完毕
	wait(NULL);
	ssize_t writebytes = write(fd,s,strlen(s));
	if ( writebytes == -1 )
	{
	        printf("The Parent Process Write To fd : %d Failed !\n", fd);
	}

	close(fd);
	return 0;
}
