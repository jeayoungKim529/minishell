/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:09 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/10 14:15:57 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

//cenvp;
//unlink(heredoc)

void	execute_wait(t_process *prcs, t_command_list *list, int flag)
{
	int	i;

	i = 0;
	while (flag == 0 && i < list->size && list->front->cmd_list->size > 0)
	{
		if (wait(g_status) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	ft_unlink(t_process *prcs, t_command_list *list)
{
	t_token_node	*cur;

	if (!list || !list->front || !list->front->redir_list || list->front->redir_list->size <= 0)
		return ;
	// if (list->front->redir_list->size > 0){}
	cur = list->front->redir_list->front;
	while (cur)
	{
		if (cur->type == TOKEN_OUT_APPEND)
			unlink(cur->token);
		cur = cur->next;
	}
}

void	finish_commands(t_process *prcs, t_command_list *list, int flag)
{
	execute_wait(prcs, list, flag);
	ft_unlink(prcs, list);
	builtin_signal_func();
}
