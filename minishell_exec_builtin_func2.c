/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:41:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/20 21:42:33 by jeakim           ###   ########.fr       */
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
	t_command	*cur;
	int			flag;

	flag = 0;
	cur = prcs->com_list->next;
	if (ft_strncmp(cur->argv, "-n", 3) == 0)
	{
		flag = 1;
		i++;
	}
	while (i < prcs->n_com)
	{
		if (cur->TYPE == TOKEN_QUOTE)
		{
			int j;
			j = -1;
			while (++j < ft_strlen(cur->argv) && cur->argv[j] != '$')
				printf(cur->argv[j]);
			printf("%s", ft_envpfind(prcs->envp, cur->argv[0] + j));
		}
		i++;
	}
	if (flag == 0)
		printf('\n');
}

void	ft_exit(t_process *prcs)
{
	int	i;
	int	flag;

	if (prcs->n_com > 2)
		printf("exit\nbash: exit: too many arguments\n");
	i = 0;
	flag = 0;
	while (i < ft_strlen(prcs->com[1]))
	{
		if (ft_isalnum(prcs->com[1][i]) == 1)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (flag == 1)
		printf("exit\nbash: exit: %s: numeric argument required\n", prcs->com[1]);
}
