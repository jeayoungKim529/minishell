/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 12:29:17 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/17 16:13:35 by jeakim           ###   ########.fr       */
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
	unsigned char	status;
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
	char			**cmd;
	int				n_cmd;
	int				t_cmd;
	t_envp			*envp;
	t_senvp			senvp;
	char			**exec_envp;
	char			**path;
	char			**path_x;
	int				prevfd;
	pid_t			pid;
	int				fd[2];
	int				std_fd[2];
	t_inout			file;
}	t_process;

void	execute_commands(t_process *prcs, t_command_list *list, int i);
void	init_process(t_process *prcs);
void	ft_error_exec(t_process *prcs, char *s, int n);
void	ft_error_exec_exit(t_process *prcs, char *s, int n);
//minishell_exec.c
void	execute_multi(t_process *prcs, t_command_node *cur, int i);
void	execute_single(t_process *prcs, t_command_node *cur);
//minishell_exec_envp.c
void	envp_func(t_process *prcs, char *envp[]);
void	init_status_envp(t_process *prcs);
char	**init_exec_envp(t_process *prcs);
void	save_pwd(t_process *prcs);
//minishell_exec_envp_utils.c
t_envp	*ft_envpfind(t_envp *env, char *key);
t_envp	*ft_envpnew(char *key, char *value);
void	ft_envpadd(t_envp *env, t_envp *new);
void	ft_envpdel(t_envp *env, char *key);
//minishell_exec_split.c
size_t	ft_strlen_split(const char *str, char c);
size_t	exec_count_num(const char *str, char c);
char	**ft_exec_split_util(char const *s, char **arr, int i, int len);
char	**ft_exec_split(char const *s, char c);
//minishell_exec_init.c
int		init_prcs(t_process *prcs, t_command_list *list, t_command_node *cur);
int		init_redirection(t_process *prcs, t_token_list *list);
void	init_path(t_process *prcs);
//minishell_exec_merge_command.c
char	**merge_command(t_process *prcs, t_token_list *token_list);
//minishell_exec_redirection.c
int		set_redirection(t_process *prcs, t_token_list *list);
int		set_redirection_read(t_process *prcs, t_token_node *cur);
int		set_redirection_write(t_process *prcs, t_token_node *cur);
int		set_single_redirection(t_process *prcs, int flag);
void	set_multi_redirection(t_process *prcs, int i);
//minishell_exec_builtin.c
int		execute_builtin(t_process *prcs, t_command_node *cur, int flag);
int		check_builtin_command(char **com);
int		ft_error_builtin(t_process *prcs, char *s, int n);
//minishell_exec_builtin_func1.c
void	ft_unset(t_process *prcs);
void	ft_export(t_process *prcs, int i);
void	ft_export_second(t_process *prcs);
void	ft_env(t_process *prcs, int flag);
//minishell_exec_builtin_func2.c
void	ft_exit(t_process *prcs);
void	ft_echo(t_process *prcs);
void	ft_pwd(t_process *prcs);
void	ft_cd(t_process *prcs);
//minishell_exec_builtin_utils.c
int		ft_atoi_exit(char *s);
int		ft_isalnum_exit(char *s);
int		check_envp_key(char *s);
void	change_pwd(t_process *prcs, char *key, char *value);
int		check_option(char *s);
//minishell_exec_pipex_open.c
void	run_process(t_process *prcs);
//minishell_exec_pipex_path.c
char	*check_path(t_process *prcs);
char	*make_basic_path(t_process *prcs);
void	is_directory(t_process *prcs);
//minishell_exec_pipex_close.c
void	finish_commands(t_process *prcs, t_command_list *list, int flag);
void	ft_unlink(t_process *prcs, t_command_list *list);
void	execute_wait(t_process *prcs, t_command_list *list, int flag);
//minishell_exec_free.c
void	free_second_char(char **s);
void	free_exec_envp(t_process *prcs);
void	free_path(t_process *prcs);
void	free_command(t_process *prcs);
void	free_envp(t_process *prcs);

#endif