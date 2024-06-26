/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/22 11:39:56 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

int		g_sig;
void	execute_commands(t_process *prcs, t_command_list *list, int i);

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
		prcs->envp->status = 1;
	return (1);
}

void	print_command_list(t_command_list *list);

int	parsing(t_command_list	*cmd_list, char *line, t_process *prcs)
{
	t_token_list	token_list;

	token_list.size = 0;
	cmd_list->size = 0;
	if (ft_strlen(line) == 0)
		return (1);
	else
		add_history(line);
	if (token_split(line, &token_list, 0) \
	|| (token_list.front->type == TOKEN_PIPE))
		return (handle_p_error(&token_list, cmd_list, prcs, 1));
	if (make_command_list(&token_list, cmd_list, 0, 0))
		return (handle_p_error(&token_list, cmd_list, prcs, 1));
	if (parse_command_list(cmd_list, prcs) == 1)
	{
		ft_unlink(prcs, cmd_list);
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
		str = readline("prompt : ");
		if (g_sig == 1)
			prcs->envp->status = 1;
		if (!str)
			break ;
		else if (parsing(list, str, prcs) == 1 || ft_strlen(str) == 0)
		{
			free(str);
			str = NULL;
			continue ;
		}
		else if (g_sig != 2)
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
