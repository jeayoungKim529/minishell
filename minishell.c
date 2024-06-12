/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:23:07 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/10 14:48:30 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

int	g_status;

void	readline_func(t_command_list *list, t_process *prcs);

void	ft_error_exec(t_process *prcs, char *s, int n)
{
	g_status = n;
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
	revert_signal();
	exit(1);
}

void	ft_error_parse(int status, char *s)
{
	ft_putstr_fd(s, 2);
    ft_putstr_fd("\n", 2);
	if (status == 2)
		exit(1);
    // revert_signal();
    // exit(status);
		// write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
	// rl_redisplay();
	// exit(status);
}


int	main(int argc, char *argv[], char *envp[])
{
	t_command_list	list;
	t_process		prcs;
	char			*line;

	builtin_signal_func();

	envp_func(&prcs, envp);
	readline_func(&list, &prcs);
	free_envp(&prcs);
	revert_signal();

	exit(0);
}
