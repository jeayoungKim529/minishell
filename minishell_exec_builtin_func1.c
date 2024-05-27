/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:22 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 19:28:41 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_process *prcs, int flag)
{
	t_envp	*cur;

	printf("env\n");
	cur = prcs->envp;
	while (cur)
	{
		if (flag == 1)
			printf("declare -x ");
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		else if (!cur->value && flag == 1)
			printf("%s\n", cur->key);
		cur = cur->next;
	}
}

void	ft_export(t_process *prcs)
{
	char	**tmp;
	int		i;

	if (prcs->n_cmd == 1)
		ft_env(prcs, 1);
	else
	{
		i = 0;
		while (++i < prcs->n_cmd)
		{
			if (ft_isalpha(prcs->cmd[i][0]) == 1)
				printf("bash: export: not a valid identifier\n");
			tmp = ft_split(prcs->cmd[i], '=');
			// if (!tmp)
			// 	ft_error();
			if (ft_envpfind(prcs->envp, tmp[0]) != NULL)
			{
				printf("bash: export: '%s': not a valid identifier\n", \
					ft_envpfind(prcs->envp, tmp[0]));
				return ;
			}
			ft_envpadd(prcs->envp, ft_envpnew(tmp[0], tmp[1]));
		}
	}
}

void	ft_unset(t_process *prcs)
{
	t_envp	*cur;
	int		i;

	i = 1;
	while (i < prcs->n_cmd)
	{
		ft_envpdel(prcs->envp, prcs->cmd[i]);
		i++;
	}
}
