/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:54 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 20:06:05 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	check_builtin_command(char **com)
{
	if (strncmp("cd", com[0], 3) == 0)
		return (1);
	else if (strncmp("pwd", com[0], 4) == 0)
		return (1);
	else if (strncmp("echo", com[0], 5) == 0)
		return (1);
	else if (strncmp("env", com[0], 4) == 0)
		return (1);
	else if (strncmp("export", com[0], 7) == 0)
		return (1);
	else if (strncmp("unset", com[0], 6) == 0)
		return (1);
	else if (strncmp("exit", com[0], 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_process *prcs)
{
	set_single_redirection(prcs);
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
	if (dup2(prcs->prevfd, 1) == -1)
		ft_error_exec(prcs, strerror(errno));
	return (-1);
}
