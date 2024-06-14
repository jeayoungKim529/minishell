/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 19:28:31 by jeakim           ###   ########.fr       */
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
	else if (execve(path, prcs->cmd, init_exec_envp(prcs)) == -1)
	{
		printf("eror:%d\n", errno);
		ft_error_exec(prcs, strerror(errno), errno);
	}
	exit (0);
}

void	other_command(t_process *prcs, int i)
{
	char	*path;

	set_multi_redirection(prcs, i);
	close(prcs->fd[0]);
	close(prcs->fd[1]);
	close(prcs->prevfd);
	run_process(prcs);
	exit(1);
}
