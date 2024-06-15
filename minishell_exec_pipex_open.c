/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 13:37:18 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	run_process(t_process *prcs)
{
	char	*path;

	if (check_builtin_command(prcs->cmd) == 1)
	{
		execute_builtin(prcs);
		exit(prcs->envp->status);
	}
	path = check_path(prcs);
	if (path == NULL && ft_strchr(prcs->cmd[0], '/') == NULL)
		ft_error_exec_exit(prcs, "command not found", 127);
	if (path == NULL && ft_strchr(prcs->cmd[0], '/') != NULL)
		ft_error_exec_exit(prcs, "No such file or directory3\n", 127);
	else if (path == NULL)
		path = prcs->cmd[0];
	else if (execve(path, prcs->cmd, init_exec_envp(prcs)) == -1)
	{
		ft_error_exec_exit(prcs, strerror(errno), errno);
	}
	exit (1);
}
