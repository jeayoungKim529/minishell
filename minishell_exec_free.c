/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:14:44 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/30 17:58:01 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

//free_command_list(cmd_list);

void	free_envp(t_process *prcs)
{
	t_envp	*cur;
	t_envp	*next;

	cur = prcs->envp;
	while (cur)
	{
		next = cur->next;
		free(cur);
		cur = next;
	}
}

void	free_command(t_process *prcs)
{
	int	i;

	i = 0;
	while (prcs->cmd && prcs->cmd[i])
	{
		free(prcs->cmd[i]);
		i++;
	}
	free(prcs->cmd);
}

void	free_path(t_process *prcs)
{
	int	i;

	if (prcs->path)
	{
		i = -1;
		while (prcs->path[++i])
			free(prcs->path[i]);
		free(prcs->path);
	}
	if (prcs->path_x)
	{
		i = -1;
		while (prcs->path_x[++i])
			free(prcs->path_x[i]);
		free(prcs->path_x);
	}
}