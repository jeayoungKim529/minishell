/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_env_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:13:15 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 16:13:52 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

int	env_split_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != '$' && s[i] != '\0')
		{
			while (s[i] != '$' && s[i] != '\0')
				i++;
		}
		else
		{
			i++;
			while (ft_isalnum(s[i]) != 0 || s[i] == '?')
			{
				i ++;
				if (s[i - 1] == '?')
					break ;
			}
		}
		count++;
	}
	return (count);
}

int	make_env_str(char *s, char **result)
{
	int	len;

	len = 1;
	while (ft_isalnum(s[len]) != 0 || s[len] == '?')
	{
		len ++;
		if (s[len - 1] == '?')
			break ;
	}
	*result = ft_substr(s, 0, len);
	return (len);
}

char	**make_env_result(char **result, char *s, int i, int idx)
{
	int		len;

	while (s[i])
	{
		len = 0;
		if (s[i] != '$' && s[i] != '\0')
		{
			while (s[i + len] != '$' && s[i + len] != '\0')
				len++;
			result[idx] = ft_substr(s, i, len);
			i += len;
		}
		else
			i += make_env_str(s, &result[idx]);
		idx ++;
	}
	result[idx] = 0;
	return (result);
}
