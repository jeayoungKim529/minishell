/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal_builtin.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:24:16 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/17 11:24:29 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	handle_signal_builtin(int signal)
{
	g_sig = 1;
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	builtin_signal_func(void)
{
	print_signal_off();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal_builtin);
}

void	revert_signal(void)
{
	print_signal_on();
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
}
