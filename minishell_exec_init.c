/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:42 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 10:13:15 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	init_path(t_process *prcs)
{
	char	*s;

	prcs->path = NULL;
	prcs->path_x = NULL;
	s = ft_envpfind(prcs->envp, "PATH");
	if (s)
		prcs->path = ft_split(ft_envpfind(prcs->envp, "PATH"), ':');
	prcs->path_x = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
	if (!prcs->path_x)
		ft_error_exec(prcs, strerror(errno));
}

void	init_redirection(t_process *prcs, t_token_list *list)
{
	t_token_node	*cur;

	cur = list->front;
	while (cur)
	{
		cur = cur->next;
	}
}

void	init_prcs(t_process *prcs, t_command_list *list)
{
	init_path(prcs);
	init_redirection(prcs, list->front->redir_list);
	init_exec_envp(prcs);
}
