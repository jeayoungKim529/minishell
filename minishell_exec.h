/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:17 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/10 12:24:42 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

typedef struct s_envp{
	char			*key;
	char			*value;
	struct s_envp	*before;
	struct s_envp	*next;
}	t_envp;

typedef struct s_senvp{
	char	*pwd;
	char	*oldpwd;
	char	*home;
}	t_senvp;

typedef struct s_inout{
	int	in;
	int	out;
}	t_inout;

typedef struct s_process{
	t_token_list	*token_list;
	char			**cmd; //free
	int				n_cmd;
	int				t_cmd;
	t_envp			*envp;
	t_senvp			senvp;
	char			**exec_envp;
	char			**path; //free
	char			**path_x; //free
	int				prevfd;
	pid_t			pid;
	int				fd[2];
	t_inout			file;
	int				status;
}	t_process;

//minishell_exec.c
void	ft_error_exec(t_process *prcs, char *s);
//minishell_exec_free.c
void	free_envp(t_process *prcs);
void	free_command(t_process *prcs);
void	free_path(t_process *prcs);
void	free_exec_envp(t_process *prcs);
void	free_second_char(char **s);
//minishell_exec_init.c
void	execute_command(t_process *prcs, t_command_list *list, int status);
void	init_prcs(t_process *prcs, t_command_list *list, t_command_node	*cur);
//minishell_envp.c
void	envp_func(t_process *prcs, char *envp[]);
void	save_pwd(t_process *prcs);
void	init_exec_envp(t_process *prcs);
//minishell_exec_envp_utils.c
t_envp	*ft_envpnew(char *key, char *value);
void	ft_envpadd(t_envp *env, t_envp *new);
void	ft_envpdel(t_envp *env, char *key);
char	*ft_envpfind(t_envp *env, char *key);
//minishell_exec.c
void	execute_commands(t_process *prcs, t_command_list *list, int *status);
void	execute_single(t_process *prcs, int i);
void	execute_multi(t_process *prcs, int i);
//minishell_exec_merge_command.c
char	**merge_command(t_process *prcs, t_token_list *cmd_list);
char	*check_envp(t_process *prcs, t_token_node *node);
//minishell_exec_builtin.c
int		execute_builtin(t_process *prcs);
int		check_builtin_command(char **com);
//minishell_exec_builtin_func1.c
void	ft_env(t_process *prcs, int flag);
void	ft_export(t_process *prcs);
void	ft_unset(t_process *prcs);
//minishell_exec_builtin_func2.c
void	ft_cd(t_process *prcs);
void	ft_pwd(t_process *prcs);
void	ft_echo(t_process *prcs);
void	ft_exit(t_process *prcs);
//minishell_exec_builtin_utilst.c
int		check_option(char *s);
void	change_pwd(t_process *prcs, char *key, char *value);
char	*check_last(char *s);
char	*change_dir(t_process *prcs, char *s);
void	ft_error_exec(t_process *prcs, char *s);
//minishell_exec_redirection.c
void	set_redirection(t_process *prcs, t_token_list *list);
void	set_single_redirection(t_process *prcs);
//minishell_exec_pipex_open.c
void	first_command(t_process *prcs);
void	last_command(t_process *prcs);
void	other_command(t_process *prcs, int i);
void	run_process(t_process *prcs);
//minishell_exec_pipex_close.c
void	finish_commands(t_process *prcs, t_command_list *list, int flag, \
	int *status);
void	ft_unlink(t_process *prcs, t_command_list *list);
void	execute_wait(t_process *prcs, t_command_list *list, int flag, \
	int *status);
//minishell_exec_pipex_path.c
char	*check_path(t_process *prcs);
char	*make_basic_path(t_process *prcs);




#endif