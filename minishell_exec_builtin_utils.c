/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 17:32:52 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

//ft_echo
int	check_option(char *s)
{
	int	i;

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

	cur = ft_envpfind(prcs->envp, key);
	if (cur == NULL)
		ft_envpadd(prcs->envp, ft_envpnew(key, value));
	else
	{
		free(cur->value);
		cur->value = NULL;
		cur->value = value;
	}
	if (ft_strncmp(key, "OLDPWD", 7) == 0)
	{
		free(prcs->senvp.oldpwd);
		prcs->senvp.oldpwd = NULL;
		prcs->senvp.oldpwd = ft_strdup(value);
	}
	else if (ft_strncmp(key, "PWD", 4) == 0)
	{
		free(prcs->senvp.pwd);
		prcs->senvp.pwd = NULL;
		prcs->senvp.pwd = ft_strdup(value);
	}
}

int	check_envp_key(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
	{
		if (ft_isalnum(s[i]) == 0 && s[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
