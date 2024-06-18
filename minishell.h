/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:33:15 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/17 20:24:02 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft_src/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	TOKEN_COMMAND,
	TOKEN_PIPE,
	TOKEN_IN_REDIRECT,
	TOKEN_OUT_REDIRECT,
	TOKEN_IN_APPEND,
	TOKEN_OUT_APPEND,
	TOKEN_SINGLE_QUOTE,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_ENV,
}	t_token_type;

typedef struct s_token_node {
	t_token_type		type;
	char				*token;
	struct s_token_node	*next;
	struct s_token_node	*prev;
}	t_token_node;

typedef struct s_token_list {
	t_token_node	*front;
	t_token_node	*rear;
	int				size;
}	t_token_list;

typedef struct s_command_node {
	t_token_list			*redir_list;
	t_token_list			*cmd_list;
	struct s_command_node	*next;
	struct s_command_node	*prev;
}	t_command_node;

typedef struct s_command_list {
	t_command_node	*front;
	t_command_node	*rear;
	int				size;
}	t_command_list;

#endif
