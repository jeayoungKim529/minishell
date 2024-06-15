/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 14:29:39 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

void	execute_commands(t_process *prcs, t_command_list *list, int i);

int	parsing(t_command_list	*cmd_list, char *line, t_process *prcs)
{
	t_token_list	token_list;

	token_list.size = 0;
	cmd_list->size = 0;
	if (token_split(line, &token_list, 0) || (token_list.size == 1 \
		&& token_list.front->type == TOKEN_PIPE))
	{
		if (token_list.size == 1)
			ft_error_parse(1, "syntax error near unexpected token");
		clear_list(&token_list);
		prcs->envp->status = 1;
		return (1);
	}
	if (make_command_list(&token_list, cmd_list, 0, 0))
	{
		clear_list(&token_list);
		free_command_list(cmd_list);
		prcs->envp->status = 1;
		return (1);
	}
	// print_command_list(cmd_list);
	parse_command_list(cmd_list, prcs);
	clear_list(&token_list);
	// print_command_list(cmd_list);
	return (0);
}

void	readline_func(t_command_list *list, t_process *prcs)
{
	char	*str;

	while (1)
	{
		if (list->front)
			free_command_list(list);
		str = readline("prompt : ");
		if (str)
		{
			if (parsing(list, str, prcs) == 1)
			{
				free(str);
				str = NULL;
				continue ;
			}
		}
		else
			break ;
		add_history(str);
		execute_commands(prcs, list, 0);
		free(str);
		str = NULL;
	}
	return ;
}
