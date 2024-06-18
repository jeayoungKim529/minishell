/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:48:40 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/18 20:17:58 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

int	is_meta(t_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_IN_APPEND
		|| type == TOKEN_OUT_APPEND || type == TOKEN_IN_REDIRECT
		|| type == TOKEN_OUT_REDIRECT)
		return (1);
	return (0);
}

int	set_re(t_token_node *t_node, t_command_node *c_node, t_token_node **node)
{
	if (t_node->next == NULL || is_meta(t_node->next->type))
	{
		ft_error_parse(1, "syntax error near unexpected token");
		return (-1);
	}
	else
		add_token_list(c_node->redir_list, t_node->next->token, t_node->type);
	*node = (*node)->next;
	return (2);
}

int	set_pipe(t_token_node *t_node, t_command_node **c_node, t_command_list *cl)
{
	if ((t_node->prev != NULL && is_meta(t_node->prev->type)) \
		|| t_node->next == NULL)
	{
		ft_error_parse(1, "syntax error near unexpected token");
		return (-1);
	}
	add_cmd_list(cl, 0, 0);
	*c_node = cl->rear;
	return (1);
}

t_command_node	*init_cmd(t_command_list *c, t_token_list *t, t_token_node **n)
{
	*n = t->front;
	add_cmd_list(c, 0, 0);
	return (c->rear);
}

int	make_command_list(t_token_list *t_list, t_command_list *str, int i, int j)
{
	t_command_node	*cmd_node;
	t_token_node	*node;

	cmd_node = init_cmd(str, t_list, &node);
	while (i < t_list->size)
	{
		if (node->type == TOKEN_PIPE)
		{
			j = set_pipe(node, &cmd_node, str);
			if (j == -1)
				return (1);
			i += j;
		}
		else if (node->token[0] == '>' || node->token[0] == '<')
		{
			j = set_re(node, cmd_node, &node);
			if (j == -1)
				return (1);
			i += j;
		}
		else
			i += add_token_list(cmd_node->cmd_list, node->token, node->type);
		node = node->next;
	}
	return (0);
}
/*

int	make_command_list2(t_token_list *token_list, t_command_list *cmdline)
{
	t_command_node	*cmd_node;
	t_token_node	*node;
	int				i;
	int	count;
	i = 0;
	count = 0;
	node = token_list->front;
	if (token_list->size == 1 && node->type == TOKEN_PIPE)
		return (ft_error_parse(1, "syntax error near unexpected token"));
	add_cmd_list(cmdline);
	cmd_node = cmdline->rear;
	while (i < token_list->size)
	{
		if (node->type == TOKEN_PIPE)
		{
			count = set_pipe(node, &cmd_node, cmdline);
			if (count == -1)
				return (1);
			i += count;
		}
		else if (node->token[0] == '>' || node->token[0] == '<')
		{
			count = set_rlist(node, cmd_node);
			if (count == -1)
				return (1);
			i += count;
			node = node->next;
		}
		else
			i += add_token_list(cmd_node->cmd_list, node->token, node->type);
		node = node->next;
	}
	return (0);
}
*/