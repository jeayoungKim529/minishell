/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/06/14 22:11:32 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft_src/libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

extern int	sig;

typedef enum e_token_type
{
    TOKEN_COMMAND,         // 명령어
    TOKEN_PIPE,            // 파이프 (|)
	TOKEN_IN_REDIRECT, // 표준입력 리다이렉션 (<)
	TOKEN_OUT_REDIRECT, // 표준출력 리다이렉션 (>)
	TOKEN_IN_APPEND, // 표준입력 추가 (히어독)(<<)
	TOKEN_OUT_APPEND, // 표준출력 추가(>>)
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

#endif
