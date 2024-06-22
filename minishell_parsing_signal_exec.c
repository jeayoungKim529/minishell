/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal_exec.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:24:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/22 11:50:34 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

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
