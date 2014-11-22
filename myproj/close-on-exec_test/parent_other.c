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


	// ϵͳĬ�� fcntl(fd, F_SETFD, 0) ������ execl ִ���ӽ���ʱ��
	// ���򿪡�ִ��ʱ�رա���ʶλ FD_CLOEXEC
	//fcntl(fd, F_SETFD, 1);
	//fcntl(fd, F_SETFD, 0);

	// �� fcntl(fd, F_SETFD, 1) ��Ч�������Ǳ�׼д�������� FD_CLOEXEC ȡ��ֱ��д1
	int tFlags = fcntl(fd, F_GETFD);
	fcntl(fd, F_SETFD, tFlags | FD_CLOEXEC );

	char *s="The Parent Process Writed !\n";

	pid_t pid = fork();
	// ������� gdb �����ӽ��̣����ڵ���֮ǰ���� follow-fork-mode��
	// set follow-fork-mode child
	// ����������õ����ӽ��̣����ӽ��̽������޷��������Ը�������
	if(pid == 0)										/* Child Process */
	{       
		printf("***** exec child *****\n");
		
		// execl("child", "./child", &fd, NULL);
		// ע�����棬�ӽ��̲��� exec ���������Ǹĳ�ֱ��д�봦��
		// ��ʱ�ļ���������ʶλ FD_CLOEXEC ����������
		// ��ʹ���������ʶλ���ӽ���һ������д��
		char *s = "The Child Process Writed !\n";
		ssize_t writebytes = write(fd, (void *)s, strlen(s));
		if ( writebytes == -1 )
		{
			printf("The Child Process Write To fd : %d Failed !\n", fd);
		}       
		
		printf("**********************\n");
		// ע����������ӽ��̣�����Ҫ�ر��ļ������������򸸽����޷�д��
		exit(0);
	}

	// �ȴ��ӽ���ִ�����
	wait(NULL);
	ssize_t writebytes = write(fd,s,strlen(s));
	if ( writebytes == -1 )
	{
	        printf("The Parent Process Write To fd : %d Failed !\n", fd);
	}

	close(fd);
	return 0;
}
