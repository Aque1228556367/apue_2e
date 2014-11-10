// 7.10 setjmp 和 longjmp 函数
// 程序清单 7-5 setjmp 和 longjmp 实例(P175)
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

	if (setjmp(jmpbuffer) != 0)
		printf("error");
	while (fgets(line, MAXLINE, stdin) != NULL)
		do_line(line);
	exit(0);
}

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
}

void cmd_add(void)
{
	int		token;

	token = get_token();
	if (token < 0)		/* an error has occurred */
		longjmp(jmpbuffer, 1);
	/* rest of processing for this command */
}

int get_token(void)
{
	/* fetch next token from line pointed to by tok_ptr */
}
