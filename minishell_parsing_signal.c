/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:53:13 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 13:51:22 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	print_signal_off(void)
{
	struct termios	term;

	if (tcgetattr(1, &term) != 0)
		return ;
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	print_signal_on(void)
{
	struct termios	term;

	if (tcgetattr(1, &term) != 0)
		return ;
	term.c_lflag |= (ECHOCTL);
	tcsetattr(1, 0, &term);
}

void	handle_signal(int signal)
{
	(void)signal;
	write(1, "\n", 1);
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
