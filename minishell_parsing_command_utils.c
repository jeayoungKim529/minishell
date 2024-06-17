/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_command_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 16:55:31 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/17 15:26:33 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

int	parse_command_list(t_command_list *list, t_process *prcs)
{
	t_command_node	*node;
	int				i;

	i = -1;
	node = list->front;
	while (++i < list->size)
	{
		set_command(node, prcs);
		if (set_heredoc(node, i, -1, prcs))
			return (1);
		node = node->next;
	}
	return (0);
}

char	*expand_env(char **str, int check, t_process *prcs)
{
	char	*temp;
	int		i;
	char	**result;

	i = 0;
	if (check)
	{
		result = env_split(*str);
		temp = *str;
		while (result[i] != NULL)
		{
			if (result[i][0] == '$')
				env_var_transform(result, prcs, i);
			i++;
		}
		*str = make_one_line(result, -1, 0);
		free_split(result);
		free(temp);
		temp = NULL;
	}
	return (*str);
}

void	set_command(t_command_node	*node, t_process *prcs)
{
	t_token_node	*c_token;
	char			*temp;
	int				i;

	i = -1;
	c_token = node->cmd_list->front;
	while (++i < node->cmd_list->size)
	{
		if (c_token->type == TOKEN_COMMAND)
		{
			if (ft_strchr(c_token->token, '$') != 0 || ft_strchr(c_token->\
				token, '\'') != 0 || ft_strchr(c_token->token, '\"') != 0)
			{
				temp = c_token->token;
				c_token->token = get_parse_command(temp, prcs, 1);
				free(temp);
				temp = NULL;
			}
		}
		c_token = c_token->next;
	}
}
