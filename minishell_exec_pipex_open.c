/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 13:26:32 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	run_process(t_process *prcs)
{
	char	*path;

	path = check_path(prcs);
	
	if (check_builtin_command(prcs->cmd) == 1)
		execute_builtin(prcs);
	else if (execve(path, prcs->cmd, prcs->exec_envp) == -1)
	{
		free(path);
		ft_error_exec(prcs, strerror(errno));
	}
}

void	other_command(t_process *prcs)
{
	char	*path;
	if (prcs->file.in == -1)
		if (dup2(prcs->prevfd, 0) == -1)
			ft_error_exec(prcs, strerror(errno));
	if (prcs->file.out == -1)
		if (dup2(prcs->fd[1], 1) == -1)
			ft_error_exec(prcs, strerror(errno));
	close(prcs->fd[0]);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	run_process(prcs);
	exit(1);
}
