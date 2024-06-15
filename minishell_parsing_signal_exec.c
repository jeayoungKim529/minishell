/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal_exec.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:24:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 12:25:45 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

// execve 함수를 실행할 때
void	handle_sigquit_exec(int signal)
{
	(void)signal;
	exit(1);
}

void	handle_sigint_exec(int signal)
{
	(void)signal;
	exit(1);
}

void	exec_signal_func(void)
{
	(void)signal;
	print_signal_on();
	signal(SIGQUIT, handle_sigquit_exec);
	signal(SIGINT, handle_sigint_exec);
}
