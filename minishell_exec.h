/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:17 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 17:15:25 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

#include "minishell.h"
#include "minishell_exec_process.h"

typedef struct s_envp{
	char			*key;
	char			*value;
	struct s_envp	*before;
	struct s_envp	*next;
}	t_envp;

typedef struct s_inout{
	int	in;
	int	out;
	int	prev;
}	t_inout;

typedef struct s_process{
	t_token_list	*token_list;
	char			**cmd;
	int				n_cmd;
	// char			**envp;
	t_envp			*envp;
	char			**path;
	char			**path_x;
	int				prevfd;
	pid_t			pid;
	int				fd[2];
	t_inout			io;
}	t_process;

//minishell_exec_init.c
void	execute_command(t_process *prcs, t_command_list *list);
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
char	**merge_command(t_process *prcs, t_token_list *cmd_list);
char	*check_envp(t_process *prcs, t_token_node *node);
//minishell_exec_builtin_check.c
int		check_builtin_command(char **com);
//minishell_exec_builtin.c
int		execute_builtin(t_process *prcs);
//minishell_exec_builtin_func1.c
void	ft_env(t_process *prcs, int flag);
void	ft_export(t_process *prcs);
void	ft_unset(t_process *prcs);
//minishell_exec_builtin_func2.c
void	ft_cd(t_process *prcs);
void	ft_pwd(t_process *prcs);
void	ft_echo(t_process *prcs);
void	ft_exit(t_process *prcs);

#endif