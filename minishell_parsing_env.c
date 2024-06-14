/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:42:03 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/12 19:37:07 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"



int	env_split_count(char *s)
{
	int	i;
	int	count;
	int	len;

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
			while (ft_isalnum(s[i]) != 0)
				i ++;
		}
		count++;
	}
	return (count);
}
char	**make_env_result(char **result, char *s)
{
	int		i;
	int		idx;
	int		len;

	i = 0;
	idx = 0;
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
			len ++;
			while (ft_isalnum(s[i + len]) != 0)
				len ++;
			result[idx] = ft_substr(s, i, len); 
			i += len;
		}
		idx ++;
	}
	return (result);
}

char	**env_split(char *s)
{
	char	**result;
	int		size;

	size = env_split_count(s);
	if (s[0] == 0)
		size = 0;
	result = (char **)ft_calloc(sizeof(char *), (size + 1));
	if (result == 0)
		return (free_split(result));
	result = make_env_result(result, s);
	if (result == 0)
		return (0);
	return (result);
}
void	env_var_transform(char **result, t_process *prcs )
{
	int	i;
	t_envp *node;
	char    *s;
	char    *temp;

	i = 0;
	// while (result[i] != NULL)
	// {
	// 	if (result[i][0] == '$')
	// 	{
			node = ft_envpfind(prcs->envp, (result[i] + 1));
			if (node!= NULL)
			{
				temp = result[i];
				result[i] = ft_strdup(node->value);
				free(temp);
				temp = NULL;
			}
		// }
		// i++;
	// }
}

void	expand_env_string(char **line, t_process *prcs) // 무조건 치환 하면 됨
{
	char	*temp;
	int		i;
	char	**result;

	i = 0;
	if (ft_strchr(*line, '$') == 0)
		return ;
	else
	{
		result = env_split(*line);
		temp = *line;
		while (result[i] != NULL)
		{
			if (result[i][0] == '$')
			env_var_transform(&result[i], prcs);
			i++;
		}
		*line = make_one_line(result);
		free_split(result);
		free(temp);
		temp = NULL;
	}
}