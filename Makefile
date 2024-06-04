# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 12:35:23 by jeakim            #+#    #+#              #
#    Updated: 2024/06/04 18:08:11 by jimchoi          ###   ########.fr        #
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
	COMFILE_FLAGS += -g3 
#-fsanitize=address
endif

SRCS = minishell.c \
		minishell_parsing_utils1.c \
		minishell_parsing_utils2.c\
		minishell_parsing_list_utils.c\
		minishell_parsing_command.c \
		minishell_parsing_signal.c\
		minishell_parsig_heredoc.c\
		\
		minishell_exec.c\
		minishell_exec_envp.c \
		minishell_exec_merge_command.c\
		minishell_exec_init.c\
		minishell_exec_builtin.c \
		minishell_exec_builtin_func1.c\
		minishell_exec_builtin_func2.c\
		minishell_exec_builtin_utils.c\
		minishell_exec_redirection.c\
		minishell_exec_free.c

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