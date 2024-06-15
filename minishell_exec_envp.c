/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_envp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:00 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 13:29:00 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

//pwd, oldpwd, home 변수를 prcs에 따로 저장해두기
void	save_pwd(t_process *prcs)
{
	t_envp	*cur;

	prcs->senvp.pwd = NULL;
	prcs->senvp.oldpwd = NULL;
	prcs->senvp.home = NULL;
	cur = ft_envpfind(prcs->envp, "PWD");
	if (cur)
		prcs->senvp.pwd = ft_strdup(cur->value);
	else
		prcs->senvp.pwd = getcwd(NULL, 0);
	cur = ft_envpfind(prcs->envp, "OLDPWD");
	if (cur)
		prcs->senvp.oldpwd = ft_strdup(cur->value);
	cur = ft_envpfind(prcs->envp, "HOME");
	if (cur)
		prcs->senvp.home = ft_strdup(cur->value);
	else
		prcs->senvp.home = "/Users/jeakim";
}

char	**init_exec_envp(t_process *prcs)
{
	t_envp	*cur;
	int		num;
	char	*temp;
	char	**exec_envp;

	num = 0;
	cur = prcs->envp->next;
	while (cur)
	{
		num++;
		cur = cur->next;
	}
	exec_envp = (char **)ft_calloc(sizeof(char *), num + 1);
	if (!exec_envp)
		ft_error_exec_exit(prcs, strerror(errno), errno);
	num = 0;
	cur = prcs->envp->next;
	while (cur)
	{
		temp = ft_strjoin(cur->key, "=");
		exec_envp[num++] = ft_strjoin(temp, cur->value);
		free(temp);
		cur = cur->next;
	}
	return (exec_envp);
}

void	init_status_envp(t_process *prcs)
{
	t_envp	*new;

	new = ft_envpnew("?", NULL);
	if (!new)
		ft_error_exec(prcs, strerror(errno), errno);
	prcs->envp = new;
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
	prcs->cmd = NULL;
	init_status_envp(prcs);
	while (envp && envp[i])
	{
		p = ft_split(envp[i], '=');
		if (!p)
			continue ;
		new = ft_envpnew(p[0], p[1]);
		if (!new)
			ft_error_exec(prcs, strerror(errno), errno);
		ft_envpadd(prcs->envp, new);
		free_second_char(p);
		i++;
	}
	save_pwd(prcs);
}
