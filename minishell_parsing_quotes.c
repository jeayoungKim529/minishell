/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:29:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/11 17:53:51 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

int	parse_quotes(char *str)
{
	int		len;
	char	quote;

	len = 0;
	quote = str[0];
	str++;
	if (ft_strchr(str, quote) == 0)
	{
		// ft_error_parse(1, "quote error");
		// return (-1);
		exit(1);
	}
	if (quote == '\"')
	{
		while (str[len] != '\"')
			len ++;
	}
	else
	{
		while (str[len] != '\'')
			len ++;
	}
	return (len + 2);
}

static char	**clean(char **result, int idx)
{
	int	i;

	i = 0;
	while (i < idx)
	{
		free(result[i]);
		result[i] = 0;
		i++;
	}
	free (result);
	result = 0;
	return (0);
}

int	count_word(char *s)
{
	int	i;
	int	count;
	int	len;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			len = parse_quotes(s + i);
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

static char	*put_words(char sep, char const *str)
{
	size_t	len;
	size_t	i;
	char	*str2;

	len = 0;
	i = 0;
	while (str[len] && str[len] != sep)
		++len;
	str2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!str2)
		return (0);
	while (i < len)
	{
		str2[i] = str[i];
		++i;
	}
	str2[i] = '\0';
	return (str2);
}

// int	make_quotes_word(char ***result, char *s)
// {
// 	int check;
// 	int len;

// 	check = 0;
// 	if (s[0] == '\"')
// 		check = 1;
// 	len = parse_quotes(s);
	
// }

// char *make_quotes_string(char *s, int len)
// {
// 	int	check;

// 	check = 0;
// 	if (s[0] == '\'')
// 		check = 1;
	
	
// }

char	**make_result(char **result, char *s, int size)
{
	int		i;
	int		idx;
	int		len;

	i = 0;
	idx = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\'')
		{
			len = parse_quotes(s + i);
			if (len > 2)
				result[idx] = ft_substr(s, i, len);
			else
				idx--;
			i += len;
		}
		else if (s[i] != ' ')
		{
			len = 0;
			while (s[i + len] != ' ' && s[i + len] != '\''
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

	size = count_word(s);
	if (s[0] == 0)
		size = 0;
	printf("split count: %d\n", size);
	result = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (result == 0)
		return (clean(result, -1));
	result = make_result(result, s, size);
	if (result == 0)
		return (0);
	return (result);
}

char *make_one_line(char **result)
{
	int		idx;
	int		len;
	int		i;
	int		j;
	char	*str;

	idx = -1;
	len = 0;
	while (result[++idx] != 0)
		len += ft_strlen(result[idx]);
	printf("split count: %d\n", len);
	str = ft_calloc(sizeof (char), len + 1);
	i = 0;
	idx = 0;
	while (i < len - 1)
	{
		j = 0;
		// printf(" i = %d\n", i);
		while (result[idx] && result[idx][j])
		{
			// printf("%d %d %d\n", i, idx,j);
			str[i] = result[idx][j];
			j++;
			i++;
		}
		idx ++;
	}
	return (str);
}

char	**expand_env_string(char ***result)
{
	char	*temp;
	int		idx;
	int		len;
	char	**line;

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
	return (result);
}

// char	*remove_quotes(char *str) 
int main()
{
	int	len;
	char *str = "''te\"\'\'st tt\"est\'tset\'";
	// char *str = "test";
	char **result;

	int i = 0;
	result = mini_split(str);
	// while(result[i] != NULL)
	// {
	// 	printf("%s\n", result[i]);
	// 	i++;
	// }
	char **line;

line = expand_env_string(result);
printf("line \n\n");
	while(line[i] != NULL)
	{
		printf("%s\n", line[i]);
		i++;
	}
make_one_line(line);

printf("line = %s\n", make_one_line(line));

	return (0);
}