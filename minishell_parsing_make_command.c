/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_make_command.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 13:47:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/24 17:37:10 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

int	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node)
{

	// < | TOKEN_VARIABLE
	// | > 가능함
	t_token_type type;
	int	count;

	count = 1;
	type = token_node->type;
	token_node = token_node->next;
	while (token_node && !is_meta(token_node->type))
	{
		if (token_node->type == TOKEN_WHITESPACE)
			break ;
		add_token_list(cmd_node->redir_list, token_node->token, type);
		token_node = token_node->next;
		count++;
	}
	if (count == 0)
	{
		printf("count is 0\n\n");
		exit(1);
	}
	return (count);
}

void make_command_list(t_token_list *token_list, t_command_list *cmdline)
{
	t_command_node *cmd_node;
	t_token_node *node;

	int	i = 0;
	int	count = 0;

	node = token_list->front;

	add_command_list(cmdline);
	cmd_node = cmdline->rear;
	while(i < token_list->size && node != NULL)
	{
		if (node->token[0] == '|')
		{
			add_command_list(cmdline); //다음 커맨드노드 생성 후 다음 노드로
			cmd_node = cmdline->rear;
			node = node->next;
			i++;
		}
		else if (node->token[0] == '>' || node->token[0] == '<')
		{
			count += set_redirect_list(node, cmd_node);
			i += count;
			while(count-- > 0)
				node = node->next;
		}
		else
		{
			add_token_list(cmd_node->cmd_list, node->token, node->type);// 커맨드 저장 다음노드 , 따옴표 제거
			node = node->next;
			i++;
		}
	}
}



