/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 21:47:20 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	ft_cd(t_process *prcs)
{
	char	*old_pwd;

	// if (access(prcs->cmd[1], X_OK) != 0)
	// 	printf("bash: cd: %s: No such file or directory\n", prcs->cmd[1]);
	old_pwd = getcwd(NULL, 0);
	if (chdir(prcs->cmd[1]) == -1)
		printf("bash: cd: %s: No such file or directory\n", prcs->cmd[1]);
	change_pwd(prcs, "OLDPWD", old_pwd);
	change_pwd(prcs, "PWD", getcwd(NULL, 0));
}

void	ft_pwd(t_process *prcs)
{
	t_envp	*cur;
	int		flag;

	cur = prcs->envp;
	flag = 0;
	while (cur)
	{
		if (ft_strncmp(cur->key, "PWD", 4) == 0){
			printf("%s\n", cur->value);
			flag = 1;
			break ;
		}
		cur = cur->next;
	}
	if (flag == 0)
		printf("%s\n", prcs->senvp.pwd);
}

void	ft_echo(t_process *prcs)
{
	int	flag;
	int	i;
	int	j;

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
		if (i == prcs->n_cmd - 1)
			printf("%s", prcs->cmd[i]);
		else
			printf("%s ", prcs->cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}

void	ft_exit(t_process *prcs)
{
	int	i;

	if (prcs->cmd[1] && prcs->cmd[1][0] && ft_isalnum(prcs->cmd[1][0]) != 2)
	{
		printf("exit\nbash: exit: %s: numeric argument required\n", prcs->cmd[1]);
		ft_error_exec(prcs, NULL);
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
			printf("exit\nbash: exit: %s: numeric argument required\n", prcs->cmd[1]);
			ft_error_exec(prcs, NULL);
		}
		i++;
	}
	ft_error_exec(prcs, NULL);
}
