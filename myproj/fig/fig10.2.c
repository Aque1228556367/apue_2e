// 10.3 signal 函数
// 程序清单 10-1 捕捉 SIGUSR1 和 SIGUSR2 的简单程序(P255)
#include "myerr.h"
#include "apue.h"

static void	sig_usr(int);	/* one handler for both signals */

int main(void)
{
	if (signal(SIGUSR1, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR1");
	if (signal(SIGUSR2, sig_usr) == SIG_ERR)
		err_sys("can't catch SIGUSR2");
	for ( ; ; )
		pause();
}

static void sig_usr(int signo)		/* argument is signal number */
{
	if (signo == SIGUSR1)
		printf("received SIGUSR1\n");
	else if (signo == SIGUSR2)
		printf("received SIGUSR2\n");
	else
		err_dump("received signal %d\n", signo);
}

// 本例当以后台方式运行：./a.out &
// 然后用 gdb attach 上去，在 singal 处设断点观察行为
// 然后执行 kill -USR1 [进程ID] 和 kill -USR2 [进程ID] 观察输出结果

// 注：
// 可用 gdb 的 handle 命令来捕捉信号：
// handle [信号名(如本例中的 SIGUSR1, SIGUSR2)] [选项]
// 选项有下面这些可选：
// nostop
// 当被调试的程序收到信号时，GDB不会停住程序的运行，但会打出消息告诉你收到这种信号。
// stop
// 当被调试的程序收到信号时，GDB会停住你的程序。
// print
// 当被调试的程序收到信号时，GDB会显示出一条信息。
// noprint
// 当被调试的程序收到信号时，GDB不会告诉你收到信号的信息。
// pass
// noignore
// 当被调试的程序收到信号时，GDB不处理信号。这表示，GDB会把这个信号交给被调试程序会处理。
// nopass
// ignore
// 当被调试的程序收到信号时，GDB不会让被调试程序来处理这个信号。
