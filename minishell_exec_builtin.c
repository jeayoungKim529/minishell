/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:54 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/20 21:23:21 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_process *prcs)
{
	if (ft_strncmp("cd", prcs->com[0], 3) == 0)
		ft_cd();
	else if (ft_strncmp("pwd", prcs->com[0], 4) == 0)
		ft_pwd();
	else if (ft_strncmp("echo", prcs->com[0], 5) == 0)
		ft_echo();
	else if (ft_strncmp("env", prcs->com[0], 4) == 0)
		ft_env();
	else if (ft_strncmp("export", prcs->com[0], 7) == 0)
		ft_export();
	else if (ft_strncmp("unset", prcs->com[0], 6) == 0)
		ft_unset();
	else if (ft_strncmp("exit", prcs->com[0], 5) == 0)
		ft_exit();
}
