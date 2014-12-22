// 7.10 setjmp 和 longjmp 函数
// 程序清单 7-5 setjmp 和 longjmp 实例(P175)
// 注：对原例程进行了一定修改，以观察 longjump 的行为
// 详见：
// http://blog.163.com/muren20062094@yeah/blog/static/1618444162011529103634600/
#include "myerr.h"
#include "apue.h"
#include <setjmp.h>

#define	TOK_ADD	   5

void	do_line(char *);
void	cmd_add(void);
int		get_token(void);

jmp_buf	jmpbuffer;
char	*tok_ptr;		/* global pointer for get_token() */

int main(void)
{
	char line[MAXLINE] = { 0 };
	sub = 0;

	printf("setjmp\n");

	if (setjmp(jmpbuffer) != 0)
		printf("error");

	// 在输出 error 后，程序又重新回到了这里 !
	printf("setjmp 2\n");

	while (fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);
	exit(0);
}

// 随便输入任意字符便能观察结果，因为 get_token() 总能返回 TOK_ADD
// 而 cmd_add 也去掉了 longjump 触发的限制条件
void do_line(char *ptr)		/* process one line of input */
{
	int	cmd;

	tok_ptr = ptr;

	while ((cmd = get_token()) > 0)
	{
		switch (cmd)
		{	/* one case for each command */
		case TOK_ADD:
				cmd_add();
				break;
		default:
			break;
		}
	}
	printf("cmd=%d\n", cmd);
}

void cmd_add(void)
{
	int		token;

	token = get_token();
	printf("token=%d\n", token);

	// 去掉这里的限制，观察 longjump 跳转到了哪里
	//if (token < 0)		/* an error has occurred */
		longjmp(jmpbuffer, 1);
	/* rest of processing for this command */
}

int get_token(void)
{
	/* fetch next token from line pointed to by tok_ptr */
	return TOK_ADD;
}
