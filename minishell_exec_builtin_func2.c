/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 17:33:05 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd()
{

}

void	ft_pwd(t_process *prcs)
{
	t_envp	*cur;

	cur = prcs->envp;
	while (cur)
	{
		if (ft_strncmp(cur->key, "PWD", 4) == 0){
			printf("%s\n", cur->value);
			break ;
		}
		cur = cur->next;
	}
}

void	ft_echo(t_process *prcs)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 1;
	if (ft_strncmp(prcs->cmd[1], "-n", 2) == 0)
	{
		j = 2;
		while (j < ft_strlen(prcs->cmd[1]))
			if (ft_strncmp(prcs->cmd[j], "n", 1))
				j++;
		if (j == ft_strlen(prcs->cmd[1]))
		{
			flag = 1;
			i++;
		}
	}
	while (i < prcs->n_cmd)
	{
		printf("%s", prcs->cmd[i]);
		i++;
	}
	if (flag == 0)
		printf("\n");
}

void	ft_exit(t_process *prcs)
{
	int	i;
	int	flag;

	if (prcs->n_cmd > 2)
		printf("exit\nbash: exit: too many arguments\n");
	i = 0;
	flag = 0;
	while (i < ft_strlen(prcs->cmd[1]))
	{
		if (ft_isalnum(prcs->cmd[1][i]) == 1)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
		printf("exit\nbash: exit: %s: numeric argument required\n", prcs->cmd[1]);
}
