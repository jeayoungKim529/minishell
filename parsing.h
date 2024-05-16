/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:41:17 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/16 19:13:16 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef PARSING_H
# define PARSING_H

#include "libft_src/libft.h"
// #include "get_next_line.h"
// #include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// #include <fcntl.h>
// #include <errno.h>
// #include <string.h>
// #include <sys/types.h>

typedef enum e_token_type
{
    TOKEN_COMMAND,         // 명령어
    TOKEN_ARGUMENT,        // 명령어의 인자
    TOKEN_PIPE,            // 파이프 (|)
    TOKEN_REDIRECT_IN,     // 입력 리다이렉션 (<)
    TOKEN_REDIRECT_OUT,    // 출력 리다이렉션 (>)
    TOKEN_REDIRECT_APPEND, // 출력 리다이렉션 (>>)
    TOKEN_SEMICOLON,       // 세미콜론 (;)
    // TOKEN_AMPERSAND,       // 백그라운드 실행 (&)
    TOKEN_QUOTE,           // 작은따옴표 또는 큰따옴표 (' 또는 ")
    TOKEN_VARIABLE,        // 환경 변수 또는 특수 변수 ($)
    TOKEN_OPERATOR,        // 연산자 (&&, ||, >) 
    // 추가적인 토큰 타입들...
    TOKEN_ERROR            // 잘못된 토큰
} t_token_type;

typedef struct s_token {
	char	**value;
	int		value_size;
	t_token_type type;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

#endif