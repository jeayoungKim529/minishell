/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:09 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 18:04:02 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_wait(t_process *prcs, t_command_list *list, int flag)
{
	int	i;
	int	status;
	int	w_pid;

	i = 0;
	while (flag == 0 && i < list->size)
	{
		w_pid = wait(&status);
		if (w_pid == -1)
			exit(EXIT_FAILURE);
		if (WIFEXITED(status) && w_pid == prcs->pid)
			prcs->envp->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status) && WTERMSIG(status) != 13)
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
			if (cur_t->type == TOKEN_IN_APPEND \
			&& access(cur_t->token, F_OK) != -1)
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
	if (prcs->file.in != -1)
	{
		close(prcs->file.in);
		prcs->file.in = -1;
	}
	if (prcs->file.out != -1)
	{
		close(prcs->file.out);
		prcs->file.out = -1;
	}
	execute_wait(prcs, list, flag);
	ft_unlink(prcs, list);
	free_path(prcs);
	builtin_signal_func();
}
