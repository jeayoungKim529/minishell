/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:48:40 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/05 15:19:35 by jimchoi          ###   ########.fr       */
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

int	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node)
{
	int count;

	count = 1;
	if (token_node->next == NULL || is_meta(token_node->next->type) )
		ft_error_parse(1, "syntax error near unexpected token");
	else
		add_token_list(cmd_node->redir_list, token_node->next->token, token_node->type);
	return (2);
}
int set_pipe(t_token_node *token_node, t_command_node **cmd_node, t_command_list *cmdline)
{
	if ((token_node->prev != NULL && is_meta(token_node->prev->type)) || token_node->next == NULL)
		ft_error_parse(1, "syntax error near unexpected token");

	add_command_list(cmdline);
	*cmd_node = cmdline->rear;
	return (1);
}

void	make_command_list(t_token_list *token_list, t_command_list *cmdline)
{
	t_command_node	*cmd_node;
	t_token_node	*node;
	int				i;
	
	i = 0;
	node = token_list->front;
	if (token_list->size == 1 && node->type == TOKEN_PIPE)
		ft_error_parse(1, "syntax error near unexpected token");
	
	add_command_list(cmdline);
	cmd_node = cmdline->rear;
	while (i < token_list->size)
	{
		if (node->type == TOKEN_PIPE )
			i += set_pipe(node, &cmd_node, cmdline);
		else if (node->token[0] == '>' || node->token[0] == '<')
		{
			i += set_redirect_list(node, cmd_node);
			node = node->next;
		}
		else
			i += add_token_list(cmd_node->cmd_list, node->token, node->type);
		node = node->next;
	}
}

