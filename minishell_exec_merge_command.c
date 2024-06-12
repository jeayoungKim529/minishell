/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_merge_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:51 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 17:48:54 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

char	**merge_command(t_process *prcs, t_token_list *token_list)
{
	int				i;
	t_token_node	*cur;
	char			**res;

	cur = token_list->front;
	prcs->n_cmd = token_list->size;
	res = (char **)ft_calloc(sizeof(char *), prcs->n_cmd + 1);
	cur = token_list->front;
	i = 0;
	while (cur && i < prcs->n_cmd)
	{
		res[i] = cur->token;
		i++;
		cur = cur->next;
	}
	return (res);
}
