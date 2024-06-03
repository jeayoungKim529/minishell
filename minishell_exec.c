/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/03 14:22:25 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_commands(t_process *prcs, t_command_list *list)
{
	t_command_node	*cur;

	if (!list)
		ft_error_exec(prcs, strerror(errno));
	cur = list->front;
	prcs->io.prev = dup(0);
	while (cur)
	{
		init_prcs(prcs);
		prcs->cmd = merge_command(prcs, cur->cmd_list);
		prcs->token_list = cur->cmd_list;
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
			execute_builtin(prcs);
		else if (list->size == 1)
		{
			fork(); //ls -l 왜 fork떠야함????????!!!!
		}
		else //pipe
		{
			//set_redirection();
			// open_pipe();
			// close_pipe();
			free_path(prcs);
		}
		free_command(prcs->cmd);
		cur = cur->next;
	}
}
