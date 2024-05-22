# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 12:35:23 by jeakim            #+#    #+#              #
#    Updated: 2024/05/22 17:20:47 by jeakim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = 

# -Wall -Werror -Wextra
NAME = minishell
LINKING_FLAGS =
#  -lreadline -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = 
# -I${HOME}/.brew/opt/readline/include
LIBFT_DIR = ./libft_src/
LIBFT = -L$(LIBFT_DIR) -lft -I./libft_src

ifdef DEBUG
	COMFILE_FLAGS += -g3 -fsanitize=address
endif

SRCS = minishell.c parsing.c parsing_utils.c list_utils.c \
		minishell_exec.c minishell_exec_envp.c minishell_exec_merge_command.c \
		minishell_exec_builtin.c minishell_exec_builtin_check.c minishell_exec_builtin_func1.c minishell_exec_builtin_func2.c

# minishell_envp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@ -I./libft_src

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)

	$(CC) -o $@ $(OBJS) $(LIBFT) $(COMFILE_FLAGS) $(LINKING_FLAGS) -lreadline


clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f last_bonus
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft