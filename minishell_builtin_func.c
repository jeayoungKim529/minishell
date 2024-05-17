/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_func.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:57:49 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/16 20:07:18 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

void	ft_cd()
{

}

void	ft_pwd()
{

}

void	ft_echo()
{

}

void	ft_env()
{

}

void	ft_export()
{

}

void	ft_unset()
{

}

void	ft_exit()
{
	
}
int	call_builtin_comment(t_info *info)
{
	if (strncmp("cd", , 3) == 0)
		ft_cd();
	else if (strncmp("pwd", , 4) == 0)
		ft_pwd();
	else if (strncmp("echo", , 5) == 0)
		ft_echo();
	else if (strncmp("env", , 4) == 0)
		ft_env();
	else if (strncmp("export", , 7) == 0)
		ft_export();
	else if (strncmp("unset", , 6) == 0)
		ft_unset();
	else if (strncmp("exit", , 5) == 0)
		ft_exit();
}
