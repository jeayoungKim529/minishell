/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:23:07 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 13:52:15 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

void	readline_func(t_command_list *list, t_process *prcs);


void	ft_error_exec(t_process *prcs, char *s)
{
	if (prcs)
		free_command(prcs);
	if (prcs->path || prcs->path_x)
		free_path(prcs);
	if (prcs->envp)
		free_envp(prcs);
	if (prcs->exec_envp)
		free_exec_envp(prcs);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command_list	list;
	t_process		prcs;
	char			*line;

	// signal_func();
	builtin_signal_func();

	envp_func(&prcs, envp);
	readline_func(&list, &prcs);
	print_signal_on();
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);

	exit(0);
}
