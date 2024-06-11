/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:22 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/11 16:44:52 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	ft_env(t_process *prcs, int flag)
{
	t_envp	*cur;

	cur = prcs->envp->next;
	while (cur)
	{
		if (flag == 1)
			printf("declare -x ");
		if (cur->value && flag == 1)
			printf("%s=%s\n", cur->key, cur->value);
		else if (cur->value)
			printf("%s=\"%s\"\n", cur->key, cur->value);
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
			if (ft_isalpha(prcs->cmd[i][0]) == 0)
			{
				ft_error_builtin("bash: export: not a valid identifier", 1);
				return ;
			}
			tmp = ft_exec_split(prcs->cmd[i], '=');
			if (!tmp)
				ft_error_exec(prcs, strerror(errno), 0);
			if (ft_envpfind(prcs->envp, tmp[0]) != NULL && tmp[1] != NULL)
			{
				free(ft_envpfind(prcs->envp, tmp[0])->value);
				ft_envpfind(prcs->envp, tmp[0])->value = ft_strdup(tmp[1]);
			}
			else if (ft_envpfind(prcs->envp, tmp[0]) == NULL)
				ft_envpadd(prcs->envp, ft_envpnew(tmp[0], tmp[1]));
			free_second_char(tmp);
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
