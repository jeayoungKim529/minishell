/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:21:13 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/17 14:46:49 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	check_directory(t_process *prcs)
{
	struct stat	*buf;

	buf = NULL;
	if (lstat(prcs->cmd[0], buf) == -1)
		ft_error_exec_exit(prcs, strerror(errno), errno);
	return (S_ISDIR(buf->st_mode));
}

char	*make_basic_path(t_process *prcs)
{
	int		i;
	int		ch;
	char	*path_p;
	char	*path;

	ch = 0;
	i = 0;
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
	while (prcs->path && prcs->path[++i] && ch == 0)
	{
		path_p = ft_strjoin(prcs->path[i], "/");
		path = ft_strjoin(path_p, prcs->cmd[0]);
		free(path_p);
		if (access(path, X_OK) == 0)
			ch = 1;
	}
	if (ch == 0)
		path = make_basic_path(prcs);
	if (path == NULL && access(prcs->cmd[0], X_OK) == 0)
		return (prcs->cmd[0]);
	if (path == NULL)
		return (NULL);
	return (path);
}
