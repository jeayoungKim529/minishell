/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_open.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 19:05:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 21:30:38 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	run_process(t_process *prcs, char** tmp_envp)
{
	char	*path;

	if (check_builtin_command(prcs->cmd) == 1)
	{
		execute_builtin(prcs, NULL, 1);
		exit(prcs->envp->status);
	}
	path = check_path(prcs);
	if (path == NULL && ft_strchr(prcs->cmd[0], '/') == NULL)
		ft_error_exec_exit(prcs, "command not found", 127);
	if (path == NULL && ft_strchr(prcs->cmd[0], '/') != NULL)
		ft_error_exec_exit(prcs, "No such file or directory", 127);
	else if (path == NULL)
		path = prcs->cmd[0];
	if (ft_strncmp(prcs->cmd[0], "./minishell", ft_strlen(prcs->cmd[0]) + 1) \
		== 0)
		path = "./minishell";
	tmp_envp = init_exec_envp(prcs);
	if (execve(path, prcs->cmd, tmp_envp) == -1)
	{
		if (ft_strchr(prcs->cmd[0], '/') == NULL)
			ft_error_exec_exit(prcs, "command not found", 127);
		is_directory(prcs);
		ft_error_exec_exit(prcs, strerror(errno), 126);
	}
	exit (1);
}
