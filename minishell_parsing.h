/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:39:58 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 13:52:40 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"
# include "minishell_exec.h"

// minishell_parsing_utils1.c 
int				parsing(t_command_list	*cmd_list, char *line, t_process *prcs);
void			readline_func(t_command_list *list, t_process *prcs);
//utils2
// minishell_parsing_utils2.c
int				parse_quotes(char *str);
int				get_cmd_length(char *str, int len);
char			*put_token(char *str);
t_token_type	set_token_type(char *str);
int				token_split(char *line, t_token_list *tmp_list, char *cmdline);
// minishell_parsing_list_utils.c
int				add_cmd_list(t_command_list *list, t_token_list *c_l, \
					t_token_list *r_l);
int				add_token_list(t_token_list *list, char *token, \
					t_token_type type);
void			del_token_list(t_token_list *list);
void			del_command_list(t_command_list *list, t_command_node *tmp);

// minishell_parsing_command.c
int				is_meta(t_token_type type);
int				set_re(t_token_node *t_node, t_command_node *c_node, \
					t_token_node **node);
int				set_pipe(t_token_node *t_node, t_command_node **c_node, \
					t_command_list *cl);
t_command_node	*init_cmd(t_command_list *c, t_token_list *t, t_token_node **n);
int				make_command_list(t_token_list *t_list, t_command_list *str, \
					int i, int j);
// minishell_parsing_signal.c
void			revert_signal(void);
void			print_signal_off(void);
void			print_signal_on(void);
void			handle_signal(int signal);
void			signal_func(void);
void			signal_off(void);
void			handle_signal_heredoc(int signal);
void			heredoc_signal_func(void);
void			handle_sigquit_exec(int signal);
void			handle_sigint_exec(int signal);
void			exec_signal_func(void);
void			handle_signal_builtin(int signal);
void			builtin_signal_func(void);
// minishell_parsing_heredoc.c
size_t			p_strlen(char *s);
void			set_heredoc(t_command_node	*node, int i, t_process *prcs);
void			set_heredoc_file(t_token_node **token_node, char *path, \
					t_process *prcs);
char			*set_heredoc_path(char *i, char *j, char *name);
void			heredoc_readline(int fd, char *token, t_process *prcs, \
					int check);
// minishell_parsing_quotes.c
int				puotes_split_count(char *s, int i, int count);
char			**make_mini_result(char **result, char *s, int i, int idx);
char			**mini_split(char *s);
void			remove_quotes(char **result, t_process *prcs, int check);
char			*get_parse_command(char *command, t_process *prcs, int check);
// minishell_parsing_quotes_utils.c
char			*make_one_line(char **result, int idx, int len);
char			**free_split(char **result);
int				get_quotes_lenght(char *str);
// minishell_parsing_env.c
int				env_split_count(char *s);
char			**make_env_result(char **result, char *s, int i, int idx);
char			**env_split(char *s);
void			env_var_transform(char **result, t_process *prcs);
void			expand_env_string(char **line, t_process *prcs);
// minishell_parsing_command_utils.c
void			parse_command_list(t_command_list *list, t_process *prcs);
char			*expand_env(char **str, int check, t_process *prcs);
void			set_command(t_command_node	*node, t_process *prcs);
// minishell_parsing_free_list.c
void			clear_list(t_token_list *list);
void			free_command_list(t_command_list *command_list);
int				ft_error_parse(int status, char *s);
void	print_command_list(t_command_list *list);
// void print_list(t_token_list *list);

#endif
