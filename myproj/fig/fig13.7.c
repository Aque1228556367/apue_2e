// 13.6 守护进程的惯例(P363)
// 程序清单 13-3 守护进程重读配置文件
#include "myerr.h"
#include "apue.h"
#include <pthread.h>
#include <syslog.h>

sigset_t	mask;

extern int already_running(void);
extern void daemonize(const char *cmd);

void reread(void)
{
	/* ... */
	printf("Func : reread\n");
}

// 我们阻塞所有信号，然后让我们创建的线程用 sigwait() 来处理这些信号
// SIGHUP 和 SIGTERM 的默认动作是终止进程，当进程接收到这两个信号时，
// 守护进程不会消亡
void* thr_fn(void *arg)
{
	int err, signo;

	for (;;)
	{
		// 等待指定信号集mask中，一个或多个信号的发生（P348）
		// 注意：在调用 sigwait() 之前，一定保证 mask 中的信号都被阻塞
		// 否则会出现时间窗口，导致信号在调用 sigwait() 之前就被递送
		err = sigwait(&mask, &signo);
		if (err != 0)
		{
			syslog(LOG_ERR, "sigwait failed");
			exit(1);
		}

		switch (signo)
		{
		case SIGHUP:
			syslog(LOG_INFO, "Re-reading configuration file");
			reread();
			break;

		case SIGTERM:
			syslog(LOG_INFO, "got SIGTERM; exiting");
			exit(0);

		default:
			syslog(LOG_INFO, "unexpected signal %d\n", signo);
		}
	}
	return(0);
}

int main(int argc, char *argv[])
{
	int					err;
	pthread_t			tid;
	char				*cmd;
	struct sigaction	sa;

	if ((cmd = strrchr(argv[0], '/')) == NULL)
		cmd = argv[0];
	else
		cmd++;

	/*
	 * Become a daemon.
	 */
	daemonize(cmd);

	/*
	 * Make sure only one copy of the daemon is running.
	 */
	if (already_running())
	{
		syslog(LOG_ERR, "daemon already running");
		exit(1);
	}

	/*
	 * Restore SIGHUP default and block all signals.
	 */
	sa.sa_handler = SIG_DFL;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGHUP, &sa, NULL) < 0)
		err_quit("%s: can't restore SIGHUP default");
	sigfillset(&mask);

	// 多线程环境下，更改线程的信号屏蔽字（阻塞而不能递送给当前进程/线程的信号集）（12.8节，P334）
	// 和单线程环境下的 sigprocmask() 函数对应（详见 P272 sigprocmask() 函数）
	if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
		err_exit(err, "SIG_BLOCK error");

	/*
	 * Create a thread to handle SIGHUP and SIGTERM.
	 */
	err = pthread_create(&tid, NULL, thr_fn, 0);
	if (err != 0)
		err_exit(err, "can't create thread");

	/*
	 * Proceed with the rest of the daemon.
	 */
	/* ... */
	sleep(10);
	exit(0);
}
