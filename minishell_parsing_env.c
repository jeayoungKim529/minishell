/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:42:03 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/10 21:04:58 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

char	*expand_env_string(char **result)
{
	char	*str;
	char	*temp;
	int		idx;

	idx = -1;

	while (result[++idx])
	{
		if (ft_strchr(result[idx], '$') == 0)
			continue ;
		if (result[idx][0] == '\'')
		{
			temp = result[idx];
			result[idx] = ft_substr(result[idx], 1, ft_strlen(result[idx]) - 2);
			free(temp);
		}
		else if (result[idx][0] == '\"')
		{
			temp = result[idx];
			result[idx] = ft_substr(result[idx], 1, ft_strlen(result[idx]) - 2);
			free(temp);
		}
	}
	return (str);
}
