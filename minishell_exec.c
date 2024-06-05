/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 15:51:33 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_wait(t_process *prcs, t_command_list *list, int flag)
{
	int	i;

	i = 0;
	while (flag == 0 && i < list->size)
	{
		if (wait(&prcs->status) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}

void	execute_single(t_process *prcs)
{
	int		status;
	char	*path;

	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno));
	if (prcs->pid == 0)
	{
		if (prcs->file.in != -1)
			if (dup2(prcs->file.in, 0) == -1)
				ft_error_exec(prcs, strerror(errno));
		if (prcs->file.out != -1)
			if (dup2(prcs->file.out, 1) == -1)
				ft_error_exec(prcs, strerror(errno));
		exec_signal_func();
		run_process(prcs);
	}
	if (wait(&status) == -1)
		exit(EXIT_FAILURE);
}

void	execute_multi(t_process *prcs, int i)
{
	int	status;

	if (pipe(prcs->fd) == -1)
		ft_error_exec(prcs, strerror(errno));
	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno));
	else if (prcs->pid == 0)
		other_command(prcs);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	prcs->prevfd = prcs->fd[0];
}

void	execute_commands(t_process *prcs, t_command_list *list)
{
	t_command_node	*cur;
	int				i;
	int				flag;

	cur = list->front;
	i = -1;
	prcs->prevfd = dup(0);
	flag = 0;
	while (cur && list->size > 0 && list->front->cmd_list->size > 0)
	{
		init_prcs(prcs, list);
		prcs->cmd = merge_command(prcs, cur->cmd_list);
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
		{
			execute_builtin(prcs);
			flag = 1;
		}
		else if (list->size == 1)
		{
			signal_off();
			execute_single(prcs);
			builtin_signal_func();
		}
		else
			execute_multi(prcs, ++i);
		free_command(prcs);
		cur = cur->next;
	}
	//execute_wait(prcs, list, flag);
	int status;
	i = 0;
	while (flag == 0 && i < list->size)
	{
		if (wait(&status) == -1)
			exit(EXIT_FAILURE);
		i++;
	}
}
