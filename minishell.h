/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 10:54:55 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/17 10:55:27 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft_src/libft.h"
#include "parsing.h"
#include "minishell_exec.h"

#include <readline/readline.h>
#include <readline/history.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// typedef enum e_token_type
// {
//     TOKEN_COMMAND,         // 명령어
//     TOKEN_ARGUMENT,        // 명령어의 인자
//     TOKEN_PIPE,            // 파이프 (|)
//     TOKEN_REDIRECT_IN,     // 입력 리다이렉션 (<)
//     TOKEN_REDIRECT_OUT,    // 출력 리다이렉션 (>)
//     TOKEN_REDIRECT_APPEND, // 출력 리다이렉션 (>>)
//     TOKEN_SEMICOLON,       // 세미콜론 (;)
//     // TOKEN_AMPERSAND,       // 백그라운드 실행 (&)
//     TOKEN_QUOTE,           // 작은따옴표 또는 큰따옴표 (' 또는 ")
//     TOKEN_VARIABLE,        // 환경 변수 또는 특수 변수 ($)
//     TOKEN_OPERATOR,        // 연산자 (&&, ||, >) 
//     // 추가적인 토큰 타입들...
//     TOKEN_ERROR            // 잘못된 토큰
// } t_token_type;

typedef enum e_redirection {
	STDIN_REDIRECT,
	STDOUT_REDIRECT,
	STDIN_APPEND,
	STDOUT_APPEND
} t_redirection;

typedef struct s_redirect {
	t_redirection redir_type; //ENUM {<, <<, >, >>} heredoc 프로세스 따서 따로 미리 처리하고 넘기기
	char* file_name; ///tmp/heredoc1
	s_redirect *next;
} t_redirect;

typedef struct s_command {
	 char*	argv; //ex) "ls -a -l" ls -> -a -> -l;
	 s_command *next;
} t_command;

typedef struct s_command_list {
	t_redirect *redir_list;
	t_command *cmd;
	s_command_list *next; //(다음파이프) ex){ < a << aa(tmp/heredoc1) < a < aaa < a ls > b < a | << qwe(tmp/heredoc2) cat > c } 파이프 전 -> 파이프 후
}	t_command_list;


#endif
