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



// void	add_front(t_token_list *list, char *token, int idx);
// void	add_rear(t_token_list *list, char *token, int idx);
// void	del_front(t_token_list *list);
// void	del_rear(t_token_list *list);
void	print_list(t_token_list *list);
void	 print_command_list(t_command_list *list);
void	token_split(char *line, t_token_list *tmp_list);
void	clear_list(t_token_list *list);
void	add_token_list(t_token_list *list, char *token, t_token_type type);
void	del_token_list(t_token_list *list);
void	add_command_list(t_command_list *list);
void	del_command_list(t_command_list *list);



#endif
