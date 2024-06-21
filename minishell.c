/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:23:07 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/21 16:26:20 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_parsing.h"
#include "minishell_exec.h"

void	readline_func(t_command_list *list, t_process *prcs, char *str);

void	ft_error_exec(t_process *prcs, char *s, int n)
{
	if (prcs->path || prcs->path_x)
		free_path(prcs);
	if (prcs)
		free_command(prcs);
	if (prcs->exec_envp)
		free_second_char(prcs->exec_envp);
	if (s != NULL)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
		revert_signal();
	}
	prcs->envp->status = n;
}

void	ft_error_exec_exit(t_process *prcs, char *s, int n)
{
	if (prcs->path || prcs->path_x)
		free_path(prcs);
	if (prcs)
		free_command(prcs);
	if (prcs->exec_envp)
		free_second_char(prcs->exec_envp);
	if (s != NULL)
	{
		ft_putstr_fd(s, 2);
		ft_putstr_fd("\n", 2);
		revert_signal();
	}
	prcs->envp->status = n;
	exit(n);
}

int	ft_error_parse(int status, char *s)
{
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	if (status == 2)
		exit(1);
	return (1);
}

void	init_process(t_process *prcs)
{
	prcs->token_list = NULL;
	prcs->cmd = NULL;
	prcs->envp = NULL;
	prcs->exec_envp = NULL;
	prcs->path = NULL;
	prcs->path_x = NULL;
	prcs->std_fd[0] = dup(0);
	prcs->std_fd[1] = dup(1);
	prcs->file.in = -1;
	prcs->file.out = -1;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command_list	list;
	t_process		prcs;
	char			*str;

	(void)argc;
	(void)argv;
	str = 0;
	list.front = NULL;
	builtin_signal_func();
	init_process(&prcs);
	envp_func(&prcs, envp);
	readline_func(&list, &prcs, str);
	free_envp(&prcs);
	revert_signal();
	exit(0);
}
