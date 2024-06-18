/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/18 20:42:21 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

void	execute_commands(t_process *prcs, t_command_list *list, int i);
int		g_sig;

int	handle_p_error(t_token_list *t, t_command_list *c, t_process *prcs, int n)
{
	if (t->size > 0)
	{
		if (t->front->type == TOKEN_PIPE)
			ft_error_parse(1, "syntax error near unexpected token");
	}
	if (n == 2)
		ft_error_parse(1, "ambiguous redirect");
	clear_list(t);
	if (c->size > 0)
		free_command_list(c);
	if (n == 3)
		prcs->envp->status = 1;
	else
		prcs->envp->status = 2;
	return (1);
}

void	print_command_list(t_command_list *list);

int	parsing(t_command_list	*cmd_list, char *line, t_process *prcs)
{
	t_token_list	token_list;

	token_list.size = 0;
	cmd_list->size = 0;
	if (ft_strlen(line) > 0)
		add_history(line);
	if (token_split(line, &token_list, 0) \
	|| (token_list.front->type == TOKEN_PIPE))
		return (handle_p_error(&token_list, cmd_list, prcs, 1));
	if (make_command_list(&token_list, cmd_list, 0, 0))
		return (handle_p_error(&token_list, cmd_list, prcs, 1));
	if (parse_command_list(cmd_list, prcs) == 1)
	{
		if (g_sig == 2)
			return (handle_p_error(&token_list, cmd_list, prcs, 3));
		return (handle_p_error(&token_list, cmd_list, prcs, 2));
	}
	clear_list(&token_list);
	return (0);
}

void	readline_func(t_command_list *list, t_process *prcs, char *str)
{
	while (1)
	{
		g_sig = 0;
		if (g_sig == 1)
			prcs->envp->status = 1;
		str = readline("prompt : ");
		if (!str)
			break ;
		else if (str && parsing(list, str, prcs) == 1)
		{
			free(str);
			str = NULL;
			continue ;
		}
		execute_commands(prcs, list, 0);
		if (list->front)
			free_command_list(list);
		free(str);
		str = NULL;
	}
	if (list->front)
		free_command_list(list);
	return ;
}
