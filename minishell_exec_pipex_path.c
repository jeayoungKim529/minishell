/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_path.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:21:13 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/03 15:26:10 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

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
	if (path == NULL)
		ft_error_exec(prcs, "command not found");
	return (path);
}
