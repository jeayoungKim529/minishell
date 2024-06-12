/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/11 20:19:27 by jeakim           ###   ########.fr       */
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
		ft_error_exec(prcs, strerror(errno), 127);
	}
}

void	other_command(t_process *prcs, int i)
{
	char	*path;

	if (prcs->file.in == -1) //입력 파일이 없는 경우, prevfd 가져오기
	{
		//printf("no input\n");
		if (dup2(prcs->prevfd, 0) == -1)
			ft_error_exec(prcs, strerror(errno), 0);
	}
	else if (dup2(prcs->file.in, 0) == -1) // 입력 파일이 있는 경우
	{
		// printf("input\n");
		ft_error_exec(prcs, strerror(errno), 0);
	}
	if (prcs->file.out == -1) //출력 파일이 없는 경우
	{
		// printf("no output\n");
		// if (i != prcs->t_cmd - 1)cat
		if (i == prcs->n_cmd - 1)
		{
			if (dup2(prcs->std_fd[1], 1) == -1)
				ft_error_exec(prcs, strerror(errno), 0);
		}
		else
			if (dup2(prcs->fd[1], 1) == -1)
				ft_error_exec(prcs, strerror(errno), 0);
	}
	else //출력 파일이 있는 경우
	{
		// printf("output\n");
		// if (dup2(prcs->file.out, 1) == -1)
		// 	ft_error_exec(prcs, strerror(errno), 0);
		if (dup2(prcs->fd[1], prcs->std_fd[1]) == -1)
			ft_error_exec(prcs, strerror(errno), 0);
		close(prcs->file.out);
	}
	close(prcs->fd[0]);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	run_process(prcs);
	exit(1);
}
