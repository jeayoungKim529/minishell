/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/27 18:50:36 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft_src/libft.h"
// #include "parsing.h"
// #include "minishell_exec.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
    TOKEN_COMMAND,         // 명령어
    TOKEN_PIPE,            // 파이프 (|)
	STDIN_REDIRECT,
	STDOUT_REDIRECT,
	STDIN_APPEND,
	STDOUT_APPEND,
    // TOKEN_ARGUMENT,        // 명령어의 인자
    // TOKEN_SEMICOLON,       // 세미콜론 (;)
    // TOKEN_AMPERSAND,       // 백그라운드 실행 (&)
    TOKEN_SINGLE_QUOTE,           // 작은따옴표 또는 큰따옴표 (' 또는 ")
    TOKEN_DOUBLE_QUOTE,           // 작은따옴표 또는 큰따옴표 (' 또는 ")
    TOKEN_VARIABLE,        // 환경 변수 또는 특수 변수 ($)
    // TOKEN_OPERATOR,        // 연산자 (&&, ||, >) 
    // 추가적인 토큰 타입들...
    // TOKEN_ERROR            // 잘못된 토큰
} t_token_type;

// typedef enum e_redirection {
// 	STDIN_REDIRECT,
// 	STDOUT_REDIRECT,
// 	STDIN_APPEND,
// 	STDOUT_APPEND
// } t_redirection;

// typedef struct s_redirect {
// 	t_redirection redir_type; //ENUM {<, <<, >, >>} heredoc 프로세스 따서 따로 미리 처리하고 넘기기
// 	char* file_name; ///tmp/heredoc1
// 	struct s_redirect *next;
// } t_redirect;

// typedef struct s_command {
// 	 char*	argv; //ex) "ls -a -l" ls -> -a -> -l;
// 	 struct s_command *next;
// } t_command;

typedef struct s_token_node {
	t_token_type type;
	char*	token; //ex) "ls -a -l" ls -> -a -> -l;
	struct s_token_node *next;
	struct s_token_node *prev;
} t_token_node;

typedef struct s_token_list {
	t_token_node *front; 
	t_token_node *rear; 
	int	size;
} t_token_list;

typedef struct s_command_node {
	t_token_list *redir_list;
	t_token_list *cmd_list;
	struct s_command_node *next; //(다음파이프) ex){ < a << aa(tmp/heredoc1) < a < aaa < a ls > b < a | << qwe(tmp/heredoc2) cat > c } 파이프 전 -> 파이프 후
	struct s_command_node *prev; //(다음파이프) ex){ < a << aa(tmp/heredoc1) < a < aaa < a ls > b < a | << qwe(tmp/heredoc2) cat > c } 파이프 전 -> 파이프 후
}	t_command_node;

typedef struct s_command_list {
	t_command_node *front; 
	t_command_node *rear; 
	int	size;
}	t_command_list;


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

typedef struct s_senvp{
	char	*pwd;
	char	*old_pwd;
	char	*home;
}	t_senvp;

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
	t_senvp			*senvp;
}	t_process;

void	readline_func(t_command_list *list, t_process *prcs);
void	print_list(t_token_list *list);
void	print_command_list(t_command_list *list);
void	token_split(char *line, t_token_list *tmp_list);
void	clear_list(t_token_list *list);
void	add_token_list(t_token_list *list, char *token, t_token_type type);
void	del_token_list(t_token_list *list);
void	add_command_list(t_command_list *list);
void	del_command_list(t_command_list *list);



//minishell_exec_init.c
void	execute_command(t_process *prcs, t_command_list *list);
//minishell_envp.c
void	envp_func(t_process *prcs, char *envp[]);
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

#endif
