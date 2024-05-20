/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:17 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/20 21:31:29 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

#include "minishell.h"
#include "minishell_exec_pipe.h"

typedef struct s_envp{
	char			*key;
	char			*value;
	struct s_envp	*before;
	struct s_envp	*next;
}	t_envp;

//minishell_envp.c
void	envp_func(t_envp *env, char *envp[]);
t_envp	*ft_envpnew(char *key, char *value);
void	ft_envpadd(t_envp *env, t_envp *new);
void	ft_envpdel(t_envp *env, char *key);
char	*ft_envpfind(t_envp *env, char *key);
//minishell_exec.c
void	execute_commands(t_process *prcs, t_command_list *list);
//minishell_exec_redirection.c
void	init_redirection();
//minishell_exec_merge_command.c
char	**merge_command(t_process *prcs, t_command *cmd);
//minishell_exec_builtin_check.c
int		check_builtin_command();
int		check_option();
int		check_option_n();
int		check_path();
int		check_arg();
//minishell_exec_builtin.c
int		execute_builtin(t_command *com);
//minishell_exec_builtin_func1.c
void	ft_env(t_process *prcs);
void	ft_export(t_process *prcs);
void	ft_unset(t_process *prcs);
//minishell_exec_builtin_func2.c
void	ft_cd(t_process *prcs);
void	ft_pwd(t_process *prcs);
void	ft_echo(t_process *prcs);
void	ft_exit(t_process *prcs);

#endif