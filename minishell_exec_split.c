/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:33:34 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/14 20:16:01 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	ft_strlen_split(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != '=')
		len++;
	return (len);
}

size_t	exec_count_num(const char *str, char c)
{
	int	flag;

	flag = 0;
	while (*str)
	{
		if (*str == c)
			flag = 1;
		str++;
	}
	if (flag == 0)
		return (1);
	else
		return (2);
}

char	**ft_exec_split_util(char const *s, char **arr, int i, int len)
{
	int	flag;

	flag = 0;
	len = ft_strlen(s + len + 1);
	arr[1] = (char *)ft_calloc(sizeof(char), len + 1);
	if (!arr[1])
		return (NULL);
	len = 0;
	while (s[i + 1])
	{
		if (flag == 0 && (s[i + 1] == '\"' || s[i + 1] == '\''))
			i++;
		else
			arr[1][len] = s[i + 1];
		i++;
		len++;
	}
	return (arr);
}

char	**ft_exec_split(char const *s, char c)
{
	char	**arr;
	int		num;
	int		i;
	int		len;

	num = exec_count_num(s, c);
	arr = (char **)ft_calloc(sizeof(char *), (num + 1));
	if (arr == NULL)
		return (NULL);
	len = ft_strlen_split(s, '=');
	arr[0] = (char *)ft_calloc(sizeof(char), len + 1);
	i = -1;
	while (s[++i] && s[i] != '=')
		arr[0][i] = s[i];
	if (num == 1)
		return (arr);
	if (num == 2 && len == ft_strlen(s) - 1)
	{
		arr[1] = ft_strdup("\"\"");
		return (arr);
	}
	if (!ft_exec_split_util(s, arr, i, len))
		return (NULL);
	return (arr);
}
