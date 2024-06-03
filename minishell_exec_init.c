/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_init.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 17:44:42 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/30 19:08:02 by jeakim           ###   ########.fr       */
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

void	init_prcs(t_process *prcs)
{
	//prcs->io.in = -1;
	init_path(prcs);
}
