/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:08:24 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/03 14:23:05 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	set_redirection(t_process *prcs, t_token_list *list)
{
	t_token_node	*cur;
	int				fd;

	cur = list->front;
	while (cur)
	{
		if (cur->type == TOKEN_OUT_REDIRECT)
			fd = open(cur->token, O_WRONLY | O_CREAT | O_TRUNC, \
				0666);
		else if (cur->type == TOKEN_OUT_APPEND)
			fd = open(cur->token, O_WRONLY | O_CREAT | O_APPEND, \
				0666);
		else if (cur->type == TOKEN_IN_REDIRECT)
		{
			fd = open(cur->token, O_RDONLY);
			if (read(fd, 0, 0) == -1)
				ft_error_exec(prcs, strerror(errno));
		}
		else if (cur->type == TOKEN_IN_APPEND)
		{
			fd = open(cur->token, O_RDONLY);
			if (read(fd, 0, 0) == -1)
				ft_error_exec(prcs, strerror(errno));
		}
		if (fd < 0)
			ft_error_exec(prcs, strerror(errno));
		cur = cur->next;
	}
}
