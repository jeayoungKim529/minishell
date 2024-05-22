/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:54 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 15:44:47 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_process *prcs)
{
	if (ft_strncmp("cd", prcs->cmd[0], 3) == 0)
		ft_cd(prcs);
	else if (ft_strncmp("pwd", prcs->cmd[0], 4) == 0)
		ft_pwd(prcs);
	else if (ft_strncmp("echo", prcs->cmd[0], 5) == 0)
		ft_echo(prcs);
	else if (ft_strncmp("env", prcs->cmd[0], 4) == 0)
		ft_env(prcs, 0);
	else if (ft_strncmp("export", prcs->cmd[0], 7) == 0)
		ft_export(prcs);
	else if (ft_strncmp("unset", prcs->cmd[0], 6) == 0)
		ft_unset(prcs);
	else if (ft_strncmp("exit", prcs->cmd[0], 5) == 0)
		ft_exit(prcs);
}
