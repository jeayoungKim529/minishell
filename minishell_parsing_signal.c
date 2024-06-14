/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:13 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/14 22:14:58 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	revert_signal(void)
{
	print_signal_on();
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}

void	print_signal_off(void)
{
	struct termios	term;

	if (tcgetattr(1, &term) != 0)// 현재 터미널의 설정을 term에 가져옴
		return;
	term.c_lflag &= ~(ECHOCTL);	// 시그널표식 출력이 true 라면 false로 변경
	tcsetattr(1, 0, &term);// 변경한 term 설정을 현재 터미널에 적용
}

void	print_signal_on(void)
{
	struct termios	term;

	if (tcgetattr(1, &term) != 0)
		return ;
	term.c_lflag |= (ECHOCTL);	// 변경한 term 설정을 현재 터미널에 적용
	tcsetattr(1, 0, &term); // 변경한 term 설정을 현재 터미널에 적용
}
void	handle_signal(int signal)
{
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
}

void	signal_func(void)
{
	write(1, "\n", 1);
	print_signal_off();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}

void	signal_off(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	print_signal_off();
}

// 히어독일때
void	handle_signal_heredoc(int signal)
{
	// sig = 131;
	(void)signal;
	// builtin_signal_func(); 
	exit(1);
}
void heredoc_signal_func(void) // 물어보기
{
	(void)signal;
	signal(SIGQUIT, SIG_IGN); // ctrl + \ 막아놓음
	signal(SIGINT, handle_signal_heredoc);
}

// execve 함수를 실행할 때
void handle_sigquit_exec(int signal)
{
	// sig = 131;
	(void)signal;
	// write(1, "\n", 1);
	write(1, "dho", 3);
	// revert_signal();
	exit(1);
}
void handle_sigint_exec(int signal)
{
	extern int sig;

	sig = 130;
	(void)signal;
	// write(1, "\n", 1);
	// write(1, "dho\n", 4);
	// printf("sigint\n");
	// dprintf(2, "dho\n");
	// revert_signal();
	exit(1);
}
void exec_signal_func(void)
{

	(void)signal;
	print_signal_on();
	signal(SIGQUIT, handle_sigquit_exec); // ctrl + \ 막아놓음
	signal(SIGINT, handle_sigint_exec);
}



// builtin ㅎㅏㅁ수이거나 그냥 prompt일 때
void handle_signal_builtin(int signal)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void builtin_signal_func(void) 
{
	// write(1, "\n", 1);
	print_signal_off();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal_builtin);
}