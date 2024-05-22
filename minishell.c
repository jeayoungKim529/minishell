/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:23:07 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/17 19:12:16 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void  ft_error()
// {
  
// }

int	main(int argc, char *argv[], char *envp[])
{
	t_command_list	list;
	t_process		prcs;
	char			*line;

	// signal_func();
	envp_func(&prcs, envp);
	// while (42)
	// {
	// 	line = readline("minishell>");
	// 	if (!line)
	// 		break ;
	// 	parsing(&list, line);
		execute_commands(&prcs, &list);
	// 	clear_data();
	// }
	exit(0);
}
