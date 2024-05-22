/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/22 16:58:06 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft_src/libft.h"
// #include "parsing.h"
// #include "minishell_exec.h"
// #include "minishell_exec_process.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

void readline_func(t_command_list *list);
// void	print_list(t_token_list *list);
// void	 print_command_list(t_command_list *list);
// void	token_split(char *line, t_token_list *tmp_list);
// void	clear_list(t_token_list *list);
// void	add_token_list(t_token_list *list, char *token, t_token_type type);
// void	del_token_list(t_token_list *list);
// void	add_command_list(t_command_list *list);
// void	del_command_list(t_command_list *list);

#endif
