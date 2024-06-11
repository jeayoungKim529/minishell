/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/11 20:30:57 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_single(t_process *prcs, int i)
{
	char	*path;

	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno), 0);
	if (prcs->pid != 0)
		signal_off();
	if (prcs->pid == 0)
	{
		if (prcs->file.in != -1)
			if (dup2(prcs->file.in, 0) == -1) // 입력 파일이 있는 경우
				ft_error_exec(prcs, strerror(errno), 0);
		if (prcs->file.out != -1)
		{
			// if (dup2(prcs->prevfd, 1) == -1)
			// 	ft_error_exec(prcs, strerror(errno), 0);
			if (dup2(prcs->file.out, 1) == -1) // 출력 파일이 있는 경우
				ft_error_exec(prcs, strerror(errno), 0);
			close(prcs->file.out);
		}
		exec_signal_func();
		run_process(prcs);
		if (dup2(1, prcs->prevfd) == -1)
			ft_error_exec(prcs, strerror(errno), 0);
	}
}

void	execute_multi(t_process *prcs, int i)
{
	if (pipe(prcs->fd) == -1)
		ft_error_exec(prcs, strerror(errno), 0);
	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error_exec(prcs, strerror(errno), 0);
	if (prcs->pid != 0)
		signal_off();
	else if (prcs->pid == 0)
	{
		exec_signal_func();
		other_command(prcs, i);
	}
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
	i = 0;
	prcs->prevfd = dup(prcs->std_fd[0]);
	flag = 0;
	printf("run\n");
	while (cur && list->size > 0 && list->front->cmd_list->size > 0)
	{
		if (init_prcs(prcs, list, cur) == -1)
			return (free_command(prcs));
		if (list->size == 1 && check_builtin_command(prcs->cmd) == 1)
		{
			execute_builtin(prcs);
			flag = 1;
		}
		else if (list->size == 1)
			execute_single(prcs, i);
		else
			execute_multi(prcs, i);
		free_command(prcs);
		cur = cur->next;
		i++;
	}
	finish_commands(prcs, list, flag);
}
