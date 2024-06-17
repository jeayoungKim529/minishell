/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/17 20:57:47 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_single(t_process *prcs, t_command_node *cur)
{
	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno), errno);
	if (prcs->pid != 0)
		signal_off();
	if (prcs->pid == 0)
	{
		if (init_redirection(prcs, cur->redir_list) == -1)
		{
			set_single_redirection(prcs, 1);
			ft_error_exec_exit(prcs, strerror(errno), 1);
		}
		set_single_redirection(prcs, 1);
		exec_signal_func();
		run_process(prcs);
		if (dup2(1, prcs->prevfd) == -1)
			ft_error_exec(prcs, strerror(errno), errno);
	}
}

void	execute_multi(t_process *prcs, t_command_node *cur, int i)
{
	if (pipe(prcs->fd) == -1)
		ft_error_exec(prcs, strerror(errno), errno);
	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno), errno);
	if (prcs->pid != 0)
		signal_off();
	else if (prcs->pid == 0)
	{
		exec_signal_func();
		if (init_redirection(prcs, cur->redir_list) == -1)
		{
			set_multi_redirection(prcs, i);
			ft_error_exec_exit(prcs, strerror(errno), 1);
		}
		set_multi_redirection(prcs, i);
		close(prcs->fd[0]);
		close(prcs->fd[1]);
		close(prcs->prevfd);
		run_process(prcs);
	}
	close(prcs->fd[1]);
	close(prcs->prevfd);
	prcs->prevfd = prcs->fd[0];
}

void	execute_commands(t_process *prcs, t_command_list *list, int i)
{
	t_command_node	*cur;
	int				flag;

	cur = list->front;
	prcs->prevfd = dup(prcs->std_fd[0]);
	flag = 0;
	prcs->t_cmd = list->size;
	while (cur && list->size > 0 && list->front->cmd_list->size > 0 && ++i >= 0)
	{
		if (init_prcs(prcs, list, cur) == -1)
			return (free_command(prcs));
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
		{
			execute_builtin(prcs, cur, 0);
			flag = 1;
		}
		else if (list->size == 1)
			execute_single(prcs, cur);
		else
			execute_multi(prcs, cur, i);
		free_command(prcs);
		free_path(prcs);
		cur = cur->next;
	}
	finish_commands(prcs, list, flag);
}
