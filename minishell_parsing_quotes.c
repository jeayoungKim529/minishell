/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_quotes.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 12:29:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/10 18:31:05 by jimchoi          ###   ########.fr       */
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

int	make_quotes_word(char ***result, char *s)
{
	int check;
	int len;

	check = 0;
	if (s[0] == '\"')
		check = 1;
	len = parse_quotes(s);
	
}

char	**make_result(char **result, char *s, int size)
{
	int		i;
	int		idx;
	int		len;

	i = 0;
	idx = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '\"' || s[i] == '\'')
		{
			len = parse_quotes(s + i);
			if (len > 2)
				result[idx] = ft_substr(s, i + 1, len - 2);
			else
				idx--;
			i += len;
		}
		else if (s[i] != ' ')
		{
			len = 0;
			while (s[i + len] != ' ' && s[i + len] != '\'' && s[i + len] != '\"' && s[i + len] != '\0')
				len ++;
			if (s[i + len] == ' ')
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

// char	*remove_quotes(char *str) 
int main()
{
	int	len;
	char *str = "''test ttest\'tset\'";
	char **result;

	int i = 0;
	result = mini_split(str);
	while(result[i] != NULL)
	{
		printf("%s", result[i]);
		i++;
	}



	return (0);
}