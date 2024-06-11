/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_split.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:33:34 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/10 18:19:44 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	ft_exec_split_len(const char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
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

char	**ft_exec_free_split(char **arr, int i)
{
	if (i == 0)
	{
		free(arr);
		return (NULL);
	}
	while (--i >= 0)
		free(arr[i]);
	free(arr);
	return (NULL);
}

char	**ft_exec_splitsep(char **arr, const char *str, char c, int num)
{
	int	i;
	int	len;

	printf("num : %d\n", num);
	// printf("splitlen : %d, totallen : %d\n", ft_split_len(str, c), ft_strlen(str));
	if (num > 1 && (ft_exec_split_len(str, c) + 1 == ft_strlen(str)))
		arr[1] = "";
	i = 0;
	while (str[i] && num > 1)
	{
		if (str[i] == c)
		{
			arr[1] = ft_strdup((char *)str);
			if (arr[1] == NULL)
			{

				printf("dup!\n");
				return (ft_exec_free_split(arr, 1));
			}
		}
		i++;
	}
	i = 0;
	len = ft_exec_split_len(str, c);
	arr[0] = (char *)ft_calloc(sizeof(char), len + 1);
	ft_strlcpy(arr[0], str, len + 1);
	arr[num] = NULL;
	return (arr);
}

char	**ft_exec_split(char const *s, char c)
{
	char	**arr;
	int		num;

	num = exec_count_num(s, c);
	arr = (char **)ft_calloc(sizeof(char *), (num + 1));
	if (arr == NULL)
		return (NULL);
	if (num > 1 && ft_exec_split_len(s, c) + 1 == ft_strlen(s))
		arr[1] = "";
	if (ft_exec_splitsep(arr, s, c, num) == NULL)
		return (NULL);
	return (arr);
}

