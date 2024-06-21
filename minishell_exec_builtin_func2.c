/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 16:30:32 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	ft_cd(t_process *prcs)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (prcs->n_cmd == 1 || access(prcs->cmd[1], X_OK) == -1)
	{
		free(old_pwd);
		if (prcs->n_cmd != 1)
			ft_error_builtin(prcs, strerror(errno), 1);
		if (chdir(prcs->senvp.home) == -1)
			ft_error_builtin(prcs, strerror(errno), errno);
		return ;
	}
	else if (prcs->n_cmd > 1 && chdir(prcs->cmd[1]) == -1)
	{
		ft_error_builtin(prcs, strerror(errno), errno);
		return ;
	}
	change_pwd(prcs, "OLDPWD", old_pwd);
	change_pwd(prcs, "PWD", getcwd(NULL, 0));
	prcs->envp->status = 0;
	if (access(prcs->cmd[1], X_OK) == -1)
		prcs->envp->status = 1;
}

void	ft_pwd(t_process *prcs)
{
	t_envp	*cur;

	cur = ft_envpfind(prcs->envp, "PWD");
	if (cur != NULL && cur->value != NULL)
		ft_printf("%s\n", cur->value);
	else
		ft_printf("%s\n", prcs->senvp.pwd);
	prcs->envp->status = 0;
}

void	print_echo(t_process *prcs, int i, int flag)
{
	if (i == prcs->n_cmd - 1 && flag == 1)
		write(1, prcs->cmd[i], ft_strlen(prcs->cmd[i]));
	else if (i == prcs->n_cmd - 1 && flag == 0)
	{
		write(1, prcs->cmd[i], ft_strlen(prcs->cmd[i]));
		write(1, "\n", 1);
	}
	else
	{
		write(1, prcs->cmd[i], ft_strlen(prcs->cmd[i]));
		write(1, " ", 1);
	}
	i++;
}

void	ft_echo(t_process *prcs)
{
	int		flag;
	int		i;

	flag = 0;
	i = 0;
	while (++i < prcs->n_cmd)
	{
		if (check_option(prcs->cmd[i]) == 0)
			flag = 1;
		else
			break ;
	}
	while (i < prcs->n_cmd)
	{
		print_echo(prcs, i, flag);
		i++;
	}
	if (prcs->n_cmd == 1)
		write(1, "\n", 1);
	prcs->envp->status = 0;
}

void	ft_exit(t_process *prcs)
{
	if (prcs->cmd[1] && ft_isalnum_exit(prcs->cmd[1]) != 1)
		ft_error_exec_exit(prcs, "exit\nnumeric argument required", 255);
	if (prcs->n_cmd > 2)
	{
		ft_error_exec(prcs, "exit\nminishell: exit: too many arguments", 1);
		return ;
	}
	if (prcs->cmd[1] && ft_isalnum_exit(prcs->cmd[1]) != 1)
		ft_error_exec_exit(prcs, "exit\nnumeric argument required", 255);
	if (!prcs->cmd[1])
		ft_error_exec_exit(prcs, NULL, prcs->envp->status);
	ft_error_exec_exit(prcs, "exit", ft_atoi_exit(prcs->cmd[1]));
}
