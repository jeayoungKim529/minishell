/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_func1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:43:22 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/19 00:16:20 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	print_env(t_envp *cur, int flag)
{
	if (flag == 1)
	{
		ft_printf("declare -x ");
		if (cur->value == NULL)
			printf("%s\n", cur->key);
		else if (cur->value && ft_strncmp(cur->value, "\"\"", 3) != 0)
			printf("%s=\"%s\"\n", cur->key, cur->value);
		else if (cur->value && ft_strncmp(cur->value, "\"\"", 3) == 0)
			printf("%s=%s\n", cur->key, cur->value);
	}
	else
	{
		if (cur->value && ft_strncmp(cur->value, "\"\"", 3) != 0)
			printf("%s=%s\n", cur->key, cur->value);
		else if (cur->value && ft_strncmp(cur->value, "\"\"", 3) == 0)
			printf("%s=\n", cur->key);
	}
}

void	ft_env(t_process *prcs, int flag)
{
	t_envp	*cur;

	cur = prcs->envp->next;
	if (prcs->n_cmd > 1 && flag == 0)
	{
		ft_printf("env: %s: No such file or directory\n", prcs->cmd[1]);
		return (ft_error_exec(prcs, NULL, 127));
	}
	while (cur)
	{
		print_env(cur, flag);
		cur = cur->next;
	}
	prcs->envp->status = 0;
}

void	ft_export(t_process *prcs, int i)
{
	int		flag;

	flag = 0;
	if (prcs->n_cmd == 1)
		return (ft_env(prcs, 1));
	while (++i < prcs->n_cmd)
	{
		if ((ft_isalnum(prcs->cmd[i][0]) != 1 && prcs->cmd[i][0] != '_') || \
			check_envp_key(prcs->cmd[i]) == 0)
		{
			ft_error_builtin(prcs, "not a valid identifier", 1);
			flag = 1;
			return ;
		}
	}
	ft_export_second(prcs);
	if (flag == 0)
		prcs->envp->status = 0;
}

void	ft_export_second(t_process *prcs)
{
	char	**tmp;
	int		i;

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
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	while (i < prcs->n_cmd)
	{
		if ((ft_isalnum(prcs->cmd[i][0]) != 1 && prcs->cmd[i][0] != '_') || \
			check_envp_key(prcs->cmd[i]) == 0)
		{
			ft_printf("minishell: unset: %s: not a valid identifier\n", \
				prcs->cmd[i]);
			ft_error_builtin(prcs, NULL, 1);
			flag = 1;
		}
		ft_envpdel(prcs->envp, prcs->cmd[i]);
		i++;
	}
	if (flag == 0)
		prcs->envp->status = 0;
}
