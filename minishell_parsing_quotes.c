/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:29:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/12 19:35:23 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

int	puotes_split_count(char *s, int i, int count)
{
	int	len;

	while (s[i])
	{
		if (s[i] == ' ' && s[i] != '\0')
		{
			while (s[i] == ' ')
				i++;
		}
		else if (s[i] == '\"' || s[i] == '\'')
		{
			len = get_quotes_lenght(s + i);
			i += len;
			if (len < 3)
				continue ;
		}
		else if (s[i] != ' ')
		{
			while (s[i] != ' ' && s[i] != '\'' && s[i] != '\"' && s[i] != '\0')
				i++;
		}
		count++;
	}
	return (count);
}

char	**make_mini_result(char **result, char *s, int i, int idx)
{
	int		len;

	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			len = get_quotes_lenght(s + i);
			if (len > 2)
				result[idx] = ft_substr(s, i, len);
			else
				idx--;
			i += len;
		}
		else
		{
			len = 0;
			while (s[i + len] != '\''
				&& s[i + len] != '\"' && s[i + len] != '\0')
				len ++;
			result[idx] = ft_substr(s, i, len);
			i += len;
		}
		idx ++;
	}
	return (result);
}

char	**mini_split(char *s)
{
	char	**result;
	int		size;

	size = puotes_split_count(s, 0, 0);
	if (s[0] == 0)
		size = 0;
	result = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (result == 0)
		return (free_split(result));
	result = make_mini_result(result, s, 0, 0);
	if (result == 0)
		return (0);
	return (result);
}

void	remove_quotes(char **result, t_process *prcs)
{
	char	*temp;
	int		idx;
	int		len;
	char	**line;

		temp = *result;
		if (**result == '\'')
			*result = ft_substr(temp, 1, ft_strlen(temp) - 2);
		else
		{
			if (**result == '\"')
				*result = ft_substr(temp, 1, ft_strlen(temp) - 2);
			else
				*result = ft_substr(temp, 0, ft_strlen(temp));
			expand_env_string(result, prcs);
		}
		free(temp);
		temp = NULL;
}

char	*get_parse_command(char *command, t_process *prcs)
{
	char	**result;
	char	*line;
	int		i;

	i = 0;
	result = mini_split(command);
	while(result[i] != NULL)
	{
		remove_quotes(&result[i], prcs);
		i++;
	}
	line = make_one_line(result);
	free_split(result);
	return (line);
}
