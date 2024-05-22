# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 12:35:23 by jeakim            #+#    #+#              #
#    Updated: 2024/05/17 13:02:50 by jeakim           ###   ########.fr        #
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



SRCS = minishell.c\

		minishell_envp.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c $< -o $@ -I./libft_src

$(NAME): $(OBJS)
	make -C $(LIBFT_DIR)

	$(CC) -o $@ $(OBJS) $(LIBFT) $(LINKING_FLAGS)


clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f last_bonus
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libft