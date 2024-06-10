/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_envp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:00 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 21:59:50 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

//pwd, oldpwd, home 변수를 prcs에 따로 저장해두기
void	save_pwd(t_process *prcs)
{
	prcs->senvp.pwd = ft_envpfind(prcs->envp, "PWD");
	prcs->senvp.oldpwd = ft_envpfind(prcs->envp, "OLDPWD");
	prcs->senvp.home = ft_envpfind(prcs->envp, "HOME");
}

void	init_exec_envp(t_process *prcs)
{
	t_envp	*cur;
	int		num;
	char	*temp;

	num = 0;
	cur = prcs->envp;
	while (cur)
	{
		num++;
		cur = cur->next;
	}
	prcs->exec_envp = (char **)ft_calloc(sizeof(char *), num + 1);
	if (!prcs->exec_envp)
		ft_error_exec(prcs, strerror(errno));
	num = 0;
	cur = prcs->envp;
	while (cur)
	{
		temp = ft_strjoin(cur->key, "=");
		prcs->exec_envp[num] = ft_strjoin(temp, cur->value);
		free(temp);
		num++;
		cur = cur->next;
	}
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
		free_second_char(p);
		i++;
	}
	save_pwd(prcs);
}
