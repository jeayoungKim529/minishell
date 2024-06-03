/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/30 19:07:37 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	open_pipe(t_process *prcs)
{
	if (pipe(prcs->fd) == -1)
		ft_error();
	prcs->pid = fork();
	if (prcs->pid == -1)
		ft_error();
	// else if (prcs->pid == 0)
	// 	execute_command(prcs);
}

// void	open_pipe(t_info *info)
// {
// 	int	i;

// 	i = -1;
// 	info->prevfd = dup(0);
// 	while (++i < info->command_num)
// 	{
// 		if (pipe(info->fd) == -1)
// 			ft_error(info, strerror(errno));
// 		info->pid = fork();
// 		if (info->pid == -1)
// 			ft_error(info, strerror(errno));
// 		else if (info->pid == 0)
// 		{
// 			if (i == 0)
// 				first_command(info);
// 			else if (i == info->command_num - 1)
// 				last_command(info);
// 			else
// 				other_command(info, i);
// 		}
// 		close(info->fd[1]);
// 		close(info->prevfd);
// 		info->prevfd = info->fd[0];
// 	}
// 	close(info->fd[0]);
// }
