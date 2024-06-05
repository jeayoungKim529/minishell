/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:13 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/05 13:52:08 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include "minishell_parsing.h"


void	eof_handler(void)
{
	struct termios term;

	if (tcgetattr(1, &term) != 0)
		return;
	term.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(1, 0, &term);

}

void	print_signal_off(void)
{
	struct termios term;

	if (tcgetattr(1, &term) != 0)// 현재 터미널의 설정을 term에 가져옴
		return;
	term.c_lflag &= ~(ECHOCTL);	// 시그널표식 출력이 true 라면 false로 변경
	tcsetattr(1, 0, &term);// 변경한 term 설정을 현재 터미널에 적용
}	
void	print_signal_on(void)
{
	struct termios term;

	if (tcgetattr(1, &term) != 0)
		return;
	term.c_lflag |= (ECHOCTL);	// 변경한 term 설정을 현재 터미널에 적용
	tcsetattr(1, 0, &term); // 변경한 term 설정을 현재 터미널에 적용
	
}
void	handle_signal(int signal)
{

	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	
}


void signal_func(void)
{
	write(1, "\n", 1);
	print_signal_off();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal);
}

void signal_off(void)
{
	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, SIG_IGN);
	print_signal_off();

}
void signal_on(void)
{
print_signal_on();

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, SIG_DFL);
}

// 히어독일때
void handle_signal_heredoc(int signal)
{
	(void)signal;
	// write(1, "\n", 1);
	exit(1);
}
void heredoc_signal_func(void) // 물어보기
{
	signal(SIGINT, handle_signal_heredoc);
}


// execve 함수일때
void handle_signal_exec(int signal)
{
	(void)signal;
	// write(1, "\n", 1);
	exit(1);
}
void exec_signal_func(void)
{
	signal_on();
	signal(SIGINT, handle_signal_exec);
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
	write(1, "\n", 1);
	print_signal_off();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal_builtin);
}