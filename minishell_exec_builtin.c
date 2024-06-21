/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:54 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 22:05:07 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	ft_error_builtin(t_process *prcs, char *s, int n)
{
	ft_putstr_fd(s, 2);
	if (s)
		ft_putstr_fd("\n", 2);
	prcs->envp->status = n;
	return (-1);
}

int	check_builtin_command(char **com)
{
	if (ft_strncmp("cd", com[0], 3) == 0)
		return (1);
	else if (ft_strncmp("pwd", com[0], 4) == 0)
		return (1);
	else if (ft_strncmp("echo", com[0], 5) == 0)
		return (1);
	else if (ft_strncmp("env", com[0], 4) == 0)
		return (1);
	else if (ft_strncmp("export", com[0], 7) == 0)
		return (1);
	else if (ft_strncmp("unset", com[0], 6) == 0)
		return (1);
	else if (ft_strncmp("exit", com[0], 5) == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_process *prcs, t_command_node *cur, int flag)
{
	if (flag == 0 && init_redirection(prcs, cur->redir_list) == -1)
		ft_error_exec_exit(prcs, strerror(errno), 1);
	if (flag == 0)
		set_single_redirection(prcs, flag);
	if (ft_strncmp("cd", prcs->cmd[0], 3) == 0)
		ft_cd(prcs);
	else if (ft_strncmp("pwd", prcs->cmd[0], 4) == 0)
		ft_pwd(prcs);
	else if (ft_strncmp("echo", prcs->cmd[0], 5) == 0)
		ft_echo(prcs);
	else if (ft_strncmp("env", prcs->cmd[0], 4) == 0)
		ft_env(prcs, 0);
	else if (ft_strncmp("export", prcs->cmd[0], 7) == 0)
		ft_export(prcs, 0);
	else if (ft_strncmp("unset", prcs->cmd[0], 6) == 0)
		ft_unset(prcs);
	else if (ft_strncmp("exit", prcs->cmd[0], 5) == 0)
		ft_exit(prcs);
	if (flag == 0)
		if (dup2(prcs->std_fd[1], 1) == -1)
			ft_error_exec_exit(prcs, strerror(errno), errno);
	return (prcs->envp->status);
}
