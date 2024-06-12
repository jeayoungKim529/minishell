/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 19:14:44 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 16:04:50 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	free_envp(t_process *prcs)
{
	t_envp	*cur;
	t_envp	*next;

	if (!prcs->envp)
		return ;
	cur = prcs->envp->next;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		cur->key = NULL;
		free(cur->value);
		cur->value = NULL;
		free(cur);
		cur = NULL;
		cur = next;
	}
	if (prcs->senvp.pwd)
		free(prcs->senvp.pwd);
	if (prcs->senvp.oldpwd)
		free(prcs->senvp.oldpwd);
	if (prcs->senvp.home)
		free(prcs->senvp.home);
	prcs->envp->next = NULL;
}

void	free_command(t_process *prcs)
{
	int	i;

	i = 0;
	while (prcs->cmd && prcs->cmd[i] != NULL)
	{
		free(prcs->cmd[i]);
		prcs->cmd[i] = NULL;
		i++;
	}
	free(prcs->cmd);
	if (prcs->file.in != -1)
		close(prcs->file.in);
	if (prcs->file.out != -1)
		close(prcs->file.out);
	prcs->cmd = NULL;
}

void	free_path(t_process *prcs)
{
	int	i;

	if (prcs->path)
	{
		i = -1;
		while (prcs->path[++i])
		{
			free(prcs->path[i]);
			prcs->path[i] = NULL;
		}
		free(prcs->path);
	}
	if (prcs->path_x)
	{
		i = -1;
		while (prcs->path_x[++i])
		{
			free(prcs->path_x[i]);
			prcs->path_x[i] = NULL;
		}
		free(prcs->path_x);
	}
	prcs->path = NULL;
	prcs->path_x = NULL;
}

void	free_exec_envp(t_process *prcs)
{
	int	i;

	i = 0;
	if (prcs->exec_envp)
	{
		while (prcs->exec_envp[i])
		{
			free(prcs->exec_envp[i]);
			prcs->exec_envp[i] = NULL;
			i++;
		}
		free(prcs->exec_envp);
	}
}

void	free_second_char(char **s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			free(s[i]);
			s[i] = NULL;
			i++;
		}
		free(s);
	}
	s = NULL;
}
