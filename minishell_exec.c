/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/27 20:57:18 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	execute_commands(t_process *prcs, t_command_list *list)
{
	t_command_node	*cur;

	if (!list)
		ft_error_exec(prcs, strerror(errno));
	cur = list->front;
	//prcs->io.prev = dup(0);
	while (cur)
	{
		printf("hello1\n");
		prcs->cmd = merge_command(prcs, cur->cmd_list);
		prcs->token_list = cur->cmd_list;
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
			execute_builtin(prcs);
		else
		{
			// init_prcs();
			// open_pipe();
			// set_redirection();
			// close_pipe();
			free_path(prcs);
		}
		free(prcs->cmd);
		cur = cur->next;
	}
}
