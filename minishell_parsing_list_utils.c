/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_list_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:40:02 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/14 19:25:50 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

int	add_token_list(t_token_list *list, char *token, t_token_type type)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == NULL)
		ft_error_parse(2, "malloc error");
	new_node->token = ft_strdup(token);
	if (new_node->token == NULL)
		ft_error_parse(2, "malloc error");
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	if (list->size == 0)
	{
		list->front = new_node;
		list->rear = new_node;
	}
	else
	{
		list->rear->next = new_node;
		new_node->prev = list->rear;
		list->rear = new_node;
	}
	list->size++;
	return (1);
}

void	del_token_list(t_token_list *list)
{
	t_token_node	*tmp;

	if (list->size > 1)
	{
		tmp = list->front;
		list->front = list->front->next;
		list->front->prev = NULL;
		free(tmp->token);
		tmp->token = NULL;
		free(tmp);
		tmp = NULL;
	}
	else
	{
		free(list->front->token);
		list->front->token = NULL;
		free(list->front);
		list->front = NULL;
	}
	list->size--;
}

int	add_cmd_list(t_command_list *list, t_token_list *c_l, t_token_list *r_l)
{
	t_command_node	*new_node;

	new_node = (t_command_node *)ft_calloc(sizeof(t_command_node), 1);
	c_l = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	r_l = (t_token_list *)ft_calloc(sizeof(t_token_list), 1);
	if (new_node == NULL || c_l == NULL || r_l == NULL)
		ft_error_parse(2, "malloc error");
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->cmd_list = c_l;
	new_node->redir_list = r_l;
	c_l->size = 0;
	r_l->size = 0;
	if (list->size == 0)
	{
		list->front = new_node;
		list->rear = new_node;
		list->size++;
		return (1);
	}
	list->rear->next = new_node;
	new_node->prev = list->rear;
	list->rear = new_node;
	list->size++;
	return (1);
}

void	del_command_list(t_command_list *list, t_command_node *tmp)
{
	if (list->size > 1)
	{
		tmp = list->front;
		list->front = list->front->next;
		list->front->prev = NULL;
		clear_list(tmp->cmd_list);
		clear_list(tmp->redir_list);
		free(tmp->cmd_list);
		tmp->cmd_list = NULL;
		free(tmp->redir_list);
		tmp->redir_list = NULL;
		free(tmp);
		tmp = NULL;
		list->size--;
		return ;
	}
	clear_list(list->front->cmd_list);
	clear_list(list->front->redir_list);
	free(list->front->cmd_list);
	list->front->cmd_list = NULL;
	free(list->front->redir_list);
	list->front->redir_list = NULL;
	free(list->front);
	list->front = NULL;
	list->size--;
}
