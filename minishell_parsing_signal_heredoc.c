/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_signal_heredoc.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 22:23:43 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 12:23:58 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	handle_signal_heredoc(int signal)
{
	(void)signal;
	exit(1);
}

void	heredoc_signal_func(void)
{
	(void)signal;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_signal_heredoc);
}
