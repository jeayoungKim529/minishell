/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:22 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 21:46:11 by jeakim           ###   ########.fr       */
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
		if (cur->value && ft_strncmp(cur->value, "\"\"", 3) == 0 && flag == 1)
			printf("%s=%s\n", cur->key, cur->value);
		else if (cur->value && flag == 1)
			printf("%s=\"%s\"\n", cur->key, cur->value);
		else if (cur->value)
			printf("%s=%s\n", cur->key, cur->value);
		else if (!cur->value && flag == 1)
			printf("%s\n", cur->key);
		cur = cur->next;
	}
}

void	ft_export(t_process *prcs, int i)
{
	char	**tmp;

	if (prcs->n_cmd == 1)
		return (ft_env(prcs, 1));
	while (++i < prcs->n_cmd)
		if (check_envp_key(prcs->cmd[i]) == 0)
			return (ft_error_exec(prcs, "bash: export: not a valid identifier", \
				1));
	i = 0;
	while (++i < prcs->n_cmd)
	{
		tmp = ft_exec_split(prcs->cmd[i], '=');
		if (!tmp)
			ft_error_exec(prcs, strerror(errno), errno);
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
