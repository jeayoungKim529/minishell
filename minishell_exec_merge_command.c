/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_merge_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:51 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/17 13:02:54 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	check_token_size(t_token_list *token_list)
{
	t_token_node	*cur;
	int				num;

	num = 0;
	cur = token_list->front;
	while (cur)
	{
		if (ft_strlen(cur->token) != 0)
			num++;
		cur = cur->next;
	}
	return (num);
}

char	**merge_command(t_process *prcs, t_token_list *token_list)
{
	int				i;
	t_token_node	*cur;
	char			**res;

	cur = token_list->front;
	prcs->n_cmd = check_token_size(token_list);
	res = (char **)ft_calloc(sizeof(char *), check_token_size(token_list) + 1);
	cur = token_list->front;
	i = 0;
	while (cur && i < prcs->n_cmd)
	{
		if (ft_strlen(cur->token) != 0)
		{
			res[i] = ft_strdup(cur->token);
			i++;
		}
		cur = cur->next;
	}
	return (res);
}
