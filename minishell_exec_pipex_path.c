/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:21:13 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/18 21:27:22 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	is_directory(t_process *prcs)
{
	struct stat	path_stat;

	if (stat(prcs->cmd[0], &path_stat) != 0)
		ft_error_exec_exit(prcs, strerror(errno), 127);
	if (S_ISDIR(path_stat.st_mode) != 0 && ft_strchr(prcs->cmd[0], '/') \
		!= NULL)
		ft_error_exec_exit(prcs, "is a directory", 126);
}

char	*make_basic_path(t_process *prcs)
{
	int		i;
	int		ch;
	char	*path_p;
	char	*path;

	ch = 0;
	i = 0;
	if (!prcs->path_x)
		return (NULL);
	while (prcs->path_x[i] && ch == 0)
	{
		path_p = ft_strjoin(prcs->path_x[i], "/");
		path = ft_strjoin(path_p, prcs->cmd[0]);
		free(path_p);
		if (access(path, X_OK) == 0)
			ch = 1;
		i++;
	}
	if (ch == 0)
		return (NULL);
	return (path);
}

char	*check_path(t_process *prcs)
{
	int		i;
	char	*path_p;
	char	*path;
	int		ch;

	ch = 0;
	i = -1;
	if (!prcs->cmd || !prcs->cmd[0])
		ft_error_exec_exit(prcs, NULL, 0);
	if (ft_envpfind(prcs->envp, "PATH") == NULL)
		ft_error_exec_exit(prcs, "No such file or directory", 127);
	while (prcs->path && prcs->path[++i] && ch == 0)
	{
		path_p = ft_strjoin(prcs->path[i], "/");
		path = ft_strjoin(path_p, prcs->cmd[0]);
		free(path_p);
		if (access(path, X_OK) == 0)
			ch = 1;
	}
	if (ch == 0 && ft_envpfind(prcs->envp, "PATH") == NULL)
		path = make_basic_path(prcs);
	if (ch == 0 && access(prcs->cmd[0], X_OK) == 0)
		return (prcs->cmd[0]);
	return (path);
}
