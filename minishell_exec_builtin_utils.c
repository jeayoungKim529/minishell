/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 22:11:16 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	check_option(char *s)
{
	int	i;

	i = 0;
	if (ft_strncmp(s, "", 1) == 0)
		return (1);
	if (ft_strlen(s) == 1 && s[i] == '-')
		return (1);
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
		cur->value = ft_strdup(value);
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
	free(value);
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

int	ft_isalnum_exit(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	if (s[i] == '-' || s[i] == '+')
	{
		if (ft_strlen(s) == 1)
			return (0);
		i++;
	}
	while (s[i])
	{
		if (ft_isalnum(s[i]) != 2)
			return (0);
		i++;
	}
	if (-2147483648 > ft_atoi(s) || ft_atoi(s) > 2147483647)
		return (0);
	return (1);
}

int	ft_atoi_exit(char *s)
{
	long long	n;

	if (!s)
		return (0);
	n = ft_atoi(s);
	if (n < 0)
	{
		while (n < 0)
			n += 256;
	}
	else if (n > 255)
	{
		while (n > 255)
			n -= 256;
	}
	return (n);
}
