/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_quotes_utils.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 16:09:28 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/14 18:01:39 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

char	*make_one_line(char **result, int idx, int len)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (result[++idx] != 0)
		len += ft_strlen(result[idx]);
	str = ft_calloc(sizeof (char), len + 1);
	idx = 1;
	while (idx < ft_atoi(result[0]) + 1)
	{
		j = 0;
		if (result[idx][0] != '\0')
		{
			while (j < ft_strlen(result[idx]))
			{
				str[i] = result[idx][j];
				j++;
				i++;
			}
		}
		idx ++;
	}
	return (str);
}

char	**free_split(char **result)
{
	int	i;
	int	len;

	i = 0;
	len = ft_atoi(result[0]) + 1;
	while (i < len)
	{
		if (result[i])
			free(result[i]);
		result[i] = 0;
		i++;
	}
	free (result);
	result = 0;
	return (0);
}

int	get_quotes_lenght(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = str[0];
	str++;
	if (quote == '\"')
	{
		while (str[len] != '\"' && str[len] != '\0')
			len ++;
	}
	else
	{
		while (str[len] != '\'' && str[len] != '\0')
			len ++;
	}
	return (len + 2);
}
