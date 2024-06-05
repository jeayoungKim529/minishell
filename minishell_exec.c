/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 13:38:29 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

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
		run_process(prcs);
	}
	if (wait(&status) == -1)
		exit(EXIT_FAILURE);
}

void	execute_multi(t_process *prcs, int i)
{
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

	cur = list->front;
	i = -1;
	prcs->prevfd = dup(0);
	while (cur && list->size > 0)
	{
		init_prcs(prcs, list);
		prcs->cmd = merge_command(prcs, cur->cmd_list);
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
			execute_builtin(prcs);
		else if (list->size == 1)
			execute_single(prcs);
		else //pipe
			execute_multi(prcs, ++i);
		free_command(prcs);
		cur = cur->next;
	}
}
