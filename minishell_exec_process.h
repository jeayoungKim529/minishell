/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_process.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:56:05 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/20 21:28:26 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_PROCESS_H
# define MINISHELL_EXEC_PROCESS_H

#include "minishell_exec.h"

typedef struct s_inout{
	int	in;
	int	out;
	int	prev;
}	t_inout;

typedef struct s_process{
	t_command	*com_list;
	char		**com;
	int			n_com;
	char		**envp;
	char		**path;
	char		**path_x;
	int			prevfd;
	pid_t		pid;
	int			fd[2];
	t_inout		io;
}	t_process;

//minishell_exec_init.c
void	execute_command(t_process *prcs, t_command);

#endif