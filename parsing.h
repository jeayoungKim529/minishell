// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parsing.h                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2024/05/16 17:41:17 by jimchoi           #+#    #+#             */
// /*   Updated: 2024/05/16 21:25:28 by jimchoi          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */



#ifndef PARSING_H
# define PARSING_H

#include "minishell.h"

void free_command_list(t_command_list *command_list);

void	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node);
void make_command_list(t_token_list *token_list, t_command_list *cmdline);
void parsing(t_command_list	*cmd_list, char *line);
 

void	add_token_list(t_token_list *list, char *token, t_token_type type);
void	del_token_list(t_token_list *list);
void	add_command_list(t_command_list *list);
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

#endif
