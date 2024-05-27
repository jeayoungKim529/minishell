/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/24 20:57:02 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ft_echo
int	check_option(char *s)
{
	int	i;

	// if (!s)
	// 	ft_error();
	i = 0;
	while (s[i])
	{
		if (i == 0 & s[i] != '-')
			return (1);
		else if (i != 0 && s[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

//ft_cd
void	change_pwd(t_process *prcs, char *key, char *value)
{
	t_envp	*cur;

	if (ft_envpfind(prcs->envp, key) == NULL)
		ft_envpadd(prcs->envp, ft_envpnew(key, value));
	else
	{
		cur = prcs->envp;
		while (cur)
		{
			if (ft_strncmp(cur->key, key, ft_strlen(key) + 1) == 0)
			{
				cur->value = value;
				break ;
			}
			cur = cur->next;
		}
	}
	if (ft_strncmp(key, "OLDPWD", 7) == 0)
		prcs->senvp->old_pwd = value;
	else if (ft_strncmp(key, "PWD", 4) == 0)
		prcs->senvp->pwd = value;
}
