/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:39:58 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/12 19:35:56 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"
# include "minishell_exec.h"



void free_command_list(t_command_list *command_list);

int	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node);
int	set_pipe(t_token_node *token_node, t_command_node **cmd_node, t_command_list *cmdline);

int make_command_list(t_token_list *token_list, t_command_list *cmdline);
// int parsing(t_command_list	*cmd_list, char *line, t_process *prcs);


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
int	token_split(char *line, t_token_list *tmp_list);



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
void	revert_signal(void);


void	parse_command_list(t_command_list *list, t_process *prcs);
char	*set_heredoc_path(t_token_node *node, char *i, char *j, char *temp);
void	set_heredoc_file(t_token_node **token_node, char *path);
void	heredoc_readline(int fd, char *end_text);

void	ft_error_parse(int status, char *s);


int		env_split_count(char *s);
char	**make_env_result(char **result, char *s);
char	**env_split(char *s);
void	expand_env_string(char **line, t_process *prcs);
char	*make_one_line(char **result);
char	**free_split(char **result);
int		get_quotes_lenght(char *str);
int		puotes_split_count(char *s, int i, int count);
char	**make_mini_result(char **result, char *s, int i, int idx);
void	remove_quotes(char **result, t_process *prcs);
char	**mini_split(char *s);
char	*get_parse_command(char *command, t_process *prcs);

#endif
