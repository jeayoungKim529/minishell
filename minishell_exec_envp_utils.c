/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_envp_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:17:36 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 22:02:32 by jeakim           ###   ########.fr       */
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
	node->key = ft_strdup(key);
	node->value = ft_strdup(value);
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