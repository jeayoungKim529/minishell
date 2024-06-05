/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/03 19:34:58 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"


void	first_command(t_process *prcs)
{
	// if (prcs->file.in > 0)
	// 	prcs->file.in = open("temp.txt", O_RDONLY);
	// else
	// 	prcs->file.in = open(prcs->argv[1], O_RDONLY);
	if (prcs->file.in == -1)
		ft_error_exec(prcs, strerror(errno));
	if (dup2(prcs->file.in, 0) == -1)
		ft_error_exec(prcs, strerror(errno));
	if (dup2(prcs->fd[1], 1) == -1)
		ft_error_exec(prcs, strerror(errno));
	close(prcs->fd[0]);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	close(prcs->file.in);
	run_process(prcs);
	exit(1);
}

void	last_command(t_process *prcs)
{
	// if (strncmp(prcs->argv[1], "here_doc", 9) == 0)
	// 	prcs->file.out = open(prcs->argv[prcs->argc - 1], O_WRONLY | O_CREAT, \
	// 	0666);
	// else
	// 	prcs->file.out = open(prcs->argv[prcs->argc - 1], \
	// 	O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (prcs->file.out == -1)
		ft_error_exec(prcs, strerror(errno));
	if (dup2(prcs->file.out, 1) == -1)
		ft_error_exec(prcs, strerror(errno));
	if (dup2(prcs->prevfd, 0) == -1)
		ft_error_exec(prcs, strerror(errno));
	close(prcs->fd[1]);
	close(prcs->fd[0]);
	close(prcs->prevfd);
	close(prcs->file.out);
	run_process(prcs);
	exit(1);
}

void	other_command(t_process *prcs)
{
	char	*path;

	if (dup2(prcs->prevfd, 0) == -1)
		ft_error_exec(prcs, strerror(errno));
	if (dup2(prcs->fd[1], 1) == -1)
		ft_error_exec(prcs, strerror(errno));
	close(prcs->fd[0]);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	run_process(prcs);
	exit(1);
}

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
	free_exec_envp(prcs);
}
