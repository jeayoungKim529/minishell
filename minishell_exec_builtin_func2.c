/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/14 13:49:49 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	ft_cd(t_process *prcs)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(prcs->cmd[1]) == -1)
	{
		ft_error_builtin(strerror(errno), errno);
		return ;
	}
	change_pwd(prcs, "OLDPWD", old_pwd);
	change_pwd(prcs, "PWD", getcwd(NULL, 0));
}

void	ft_pwd(t_process *prcs)
{
	t_envp	*cur;

	cur = ft_envpfind(prcs->envp, "PWD");
	if (cur != NULL && cur->value != NULL)
		printf("%s\n", cur->value);
	else
		printf("%s\n", prcs->senvp.pwd);
}

void	ft_echo(t_process *prcs)
{
	int	flag;
	int	i;

	flag = 0;
	i = 1;
	while (i < prcs->n_cmd)
	{
		if (check_option(prcs->cmd[i]) == 0)
			flag = 1;
		else
			break ;
		i++;
	}
	while (i < prcs->n_cmd)
	{
		if (i == prcs->n_cmd - 1 && flag == 1)
			write(1, prcs->cmd[i], ft_strlen(prcs->cmd[i]));
		else if (i == prcs->n_cmd - 1 && flag == 0)
			write(1, ft_strjoin(prcs->cmd[i], "\n"), \
				ft_strlen(ft_strjoin(prcs->cmd[i], "\n")));
		else
			write(1, ft_strjoin(prcs->cmd[i], " "), \
				ft_strlen(ft_strjoin(prcs->cmd[i], " ")));
		i++;
	}
}

void	ft_exit(t_process *prcs)
{
	int	i;

	if (prcs->cmd[1] && prcs->cmd[1][0] && ft_isalnum(prcs->cmd[1][0]) != 2)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", prcs->cmd[1]);
		prcs->envp->status = 1;
		exit(255);
	}
	if (prcs->n_cmd > 2)
	{
		printf("exit\nbash: exit: too many arguments\n");
		return ;
	}
	i = 0;
	while (i < ft_strlen(prcs->cmd[1]))
	{
		if (ft_isalnum(prcs->cmd[1][i]) != 2)
		{
			printf("exit\nbash: exit: %s: numeric argument required\n", \
				prcs->cmd[1]);
			ft_error_exec_exit(prcs, NULL, 255);
		}
		i++;
	}
	prcs->envp->status = 0;
	ft_error_exec_exit(prcs, NULL, 0);
}
