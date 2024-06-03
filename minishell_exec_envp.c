/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_envp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:00 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/27 20:49:37 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	print_envp(t_process *prcs)
{
	t_envp	*cur;

	printf("envp\n");
	cur = prcs->envp;
	printf("%s=%s\n", cur->key, cur->value);
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
}

void	ft_envpdel(t_envp *env, char *key)
{
	t_envp	*before;
	t_envp	*node;

	if (!env)
		return ;
	node = env;
	before = env;
	while (node)
	{
		if (ft_strncmp(node->key, key, ft_strlen(key) + 1) == 0)
			break ;
		else
		{
			before = node;
			node = node->next;
		}
	}
	if (before == env)
		env = node->next;
	else
		before->next = node->next;
	free(node);
}

void	ft_envpadd(t_envp *env, t_envp *new)
{
	t_envp	*node;

	if (!env)
		env = new;
	else
	{
		node = env;
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
}

t_envp	*ft_envpnew(char *key, char *value)
{
	t_envp	*node;

	node = (t_envp *)malloc(sizeof(t_envp));
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->before = NULL;
	node->next = NULL;
	return (node);
}

char	*ft_envpfind(t_envp *env, char *key)
{
	t_envp	*cur;

	cur = env;
	while (cur)
	{
		if (ft_strncmp(key, cur->key, ft_strlen(key) + 1) == 0)
			return (cur->value);
		cur = cur->next;
	}
	return (NULL);
}

//pwd, oldpwd, home 변수를 prcs에 따로 저장해두기
void	save_pwd(t_process *prcs)
{
	// t_envp	*cur;

	// cur = prcs->envp;
	// while (cur)
	// {
	// 	if (strncmp(cur->key, "PWD", 4) == 0)
	// 		prcs->senvp->pwd = cur->value;
	// 	else if (strncmp(cur->key, "OLD_PWD", 8) == 0)
	// 		prcs->senvp->oldpwd = cur->value;
	// 	else if (strncmp(cur->key, "HOME", 5) == 0)
	// 		prcs->senvp->home = cur->value;
	// 	cur = cur->next;
	// }
	// printf("setting : pwd=%s, oldpwd=%s\n", prcs->senvp->pwd, \
	// 	prcs->senvp->oldpwd);
	prcs->senvp.pwd = ft_envpfind(prcs->envp, "PWD");
	prcs->senvp.oldpwd = ft_envpfind(prcs->envp, "OLDPWD");
	prcs->senvp.home = ft_envpfind(prcs->envp, "HOME");
}

//main에서 받아온 envp를 prcs에 연결리스트로 저장
void	envp_func(t_process *prcs, char *envp[])
{
	int		i;
	t_envp	*cur;
	t_envp	*new;
	char	**p;

	i = 0;
	prcs->envp = NULL;
	if (!envp || !envp[0])
		ft_error_exec(prcs, strerror(errno));
	while (envp && envp[i])
	{
		p = ft_split(envp[i], '=');
		if (!p)
			continue ;
		new = ft_envpnew(p[0], p[1]);
		if (!new)
			ft_error_exec(prcs, strerror(errno));
		if (i == 0)
			prcs->envp = new;
		else
			ft_envpadd(prcs->envp, new);
		free(p);
		i++;
	}
	save_pwd(prcs);
}
