/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:39:58 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/05 13:52:21 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"



void free_command_list(t_command_list *command_list);

int	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node);
int	set_pipe(t_token_node *token_node, t_command_node **cmd_node, t_command_list *cmdline);

void make_command_list(t_token_list *token_list, t_command_list *cmdline);
void parsing(t_command_list	*cmd_list, char *line);


int	add_token_list(t_token_list *list, char *token, t_token_type type);
void	del_token_list(t_token_list *list);
int	add_command_list(t_command_list *list);
void	del_command_list(t_command_list *list);

void print_command_list(t_command_list *list);
void print_list(t_token_list *list);

void	clear_list(t_token_list *list);
int	parse_quotes(char *str);
int	get_cmd_length(char *str);
char	*put_token(char *str);
void quotes_check(char *line);
t_token_type set_token_type(char *str);
void	token_split(char *line, t_token_list *tmp_list);



void	print_signal_off(void);
void	print_signal_on(void);
void	handle_signal(int signal);
void	handle_signal_heredoc(int signal);
void	heredoc_signal_func(void);
void signal_off(void);
void signal_on(void);
void builtin_signal_func(void);
void handle_signal_builtin(int signal);
void handle_signal_exec(int signal);
void exec_signal_func(void);
void	signal_func(void);


void	set_heredoc(t_command_list *list);
char	*set_heredoc_path(t_token_node *node, char *i, char *j, char *temp);
void	set_heredoc_file(t_token_node **token_node, char *path);
void	heredoc_readline(int fd, char *end_text);


#endif
