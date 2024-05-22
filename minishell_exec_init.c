/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:42 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/17 17:49:51 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_redirection()
{

}

void	init_path(t_process *prcs, char *envp[])
{
	int	i;

	i = 0;
	if (!envp)
		return ;
	while (prcs->envp[i])
	{
		if (strncmp(prcs->envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	prcs->path = ft_split(prcs->envp[i] + 5, ':');
}

void	init_path_x(t_process *prcs)
{
	prcs->path_x = ft_split("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", ':');
}

void	init_prcs(t_process *prcs)
{
	//prcs->io.in = -1;
	init_path(prcs);
	if (!path_x)
		init_path_x(prcs);
	init_redirection(prcs);
}
