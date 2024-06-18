/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_env_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:13:15 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/17 10:25:29 by jimchoi          ###   ########.fr       */
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
			while (ft_isalnum(s[i]) != 0 || s[i] == '?' || s[i] == '_')
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

char	*make_env_str(char *s, int *i)
{
	int	len;

	len = 1;
	while (ft_isalnum(s[len]) != 0 || s[len] == '?' || s[len] == '_')
	{
		len ++;
		if (s[len - 1] == '?')
			break ;
	}
	*i += len;
	return (ft_substr(s, 0, len));
}

char	**make_env_result(char **result, char *s)
{
	int	len;
	int	i;
	int	idx;

	i = 0;
	idx = 1;
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
		{
			result[idx] = make_env_str(s + i, &i);
		}
		idx ++;
	}
	result[idx] = NULL;
	return (result);
}
