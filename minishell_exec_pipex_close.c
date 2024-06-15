/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:09 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 14:38:03 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_wait(t_process *prcs, t_command_list *list, int flag)
{
	int	i;
	int	status;

	i = 0;
	while (flag == 0 && i < list->size && list->front->cmd_list->size > 0)
	{
		if (wait(&status) == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(status))
			prcs->envp->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			prcs->envp->status = WTERMSIG(status) + 128;
		i++;
	}
}

void	ft_unlink(t_process *prcs, t_command_list *list)
{
	t_command_node	*cur_l;
	t_token_node	*cur_t;

	if (prcs->file.in == -1)
		close(prcs->file.in);
	if (prcs->file.out == -1)
		close(prcs->file.out);
	if (!list || !list->front || !list->front->redir_list || \
		list->front->redir_list->size <= 0)
		return ;
	cur_l = list->front;
	while (cur_l)
	{
		cur_t = cur_l->redir_list->front;
		while (cur_t)
		{
			if (cur_t->type == TOKEN_IN_APPEND)
				unlink(cur_t->token);
			cur_t = cur_t->next;
		}
		cur_l = cur_l->next;
	}
}

void	finish_commands(t_process *prcs, t_command_list *list, int flag)
{
	if (list->front->cmd_list->size > 1)
		close(prcs->prevfd);
	execute_wait(prcs, list, flag);
	free_path(prcs);
	ft_unlink(prcs, list);
	builtin_signal_func();
}
