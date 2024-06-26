/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:42 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/19 00:14:02 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	init_path(t_process *prcs)
{
	char	*s;
	t_envp	*dst;

	prcs->path = NULL;
	prcs->path_x = NULL;
	dst = ft_envpfind(prcs->envp, "PATH");
	if (dst != NULL)
	{
		s = dst->value;
		prcs->path = ft_split(s, ':');
	}
	if (ft_envpfind(prcs->envp, "PATH") == NULL)
		prcs->path_x = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", \
			':');
	else
		prcs->path_x = NULL;
}

int	init_redirection(t_process *prcs, t_token_list *list)
{
	if (prcs->file.in != -1)
		close (prcs->file.in);
	if (prcs->file.out != -1)
		close (prcs->file.out);
	prcs->file.in = -1;
	prcs->file.out = -1;
	if (list && list->size > 0)
		return (set_redirection(prcs, list));
	return (1);
}

int	init_prcs(t_process *prcs, t_command_list *list, t_command_node *cur)
{
	prcs->n_cmd = list->front->cmd_list->size;
	init_path(prcs);
	prcs->cmd = merge_command(prcs, cur->cmd_list);
	return (0);
}
