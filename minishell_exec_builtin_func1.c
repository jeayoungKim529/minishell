/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:22 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/20 17:52:23 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_process *prcs)
{
	t_envp	*cur;

	cur = prcs->envp;
	while (cur)
	{
		if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		else if (!cur->value)
			printf("%s\n", cur->key);
		cur = cur->next;
	}
}

void	ft_export(t_process *prcs)
{
	t_envp	*new;
	char	**vk;
	int		i;

	if (prcs->n_com == 1)
		ft_env(prcs);
	else
	{
		i = 1;
		while (i < prcs->n_com)
		{
			if (ft_isalpha(com[i][0]) == 1)
				printf("not a valid identifier\n");
			// vk = ft_split(com[i], '='); ???????????
			// if (!vk)
			// 	ft_error();
			new = ft_envpnew(vk[0], vk[1]);
			ft_envpadd(prcs->envp, new);
			i++;
		}
	}
}

void	ft_unset(t_process *prcs)
{
	t_envp	*cur;
	int		i;

	i = 1;
	while (i < prcs->n_com)
	{
		ft_envpdel(prcs->envp, prcs->com[i]);
		i++;
	}
}
