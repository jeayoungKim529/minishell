/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_env.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:42:03 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 16:13:47 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

char	**env_split(char *s)
{
	char	**result;
	int		size;

	size = env_split_count(s);
	if (s[0] == 0)
		size = 0;
	result = (char **)ft_calloc(sizeof(char *), (size + 2));
	if (result == 0)
		return (free_split(result));
	result[0] = ft_itoa(size);
	result = make_env_result(result, s, 0, 1);
	if (result == 0)
		return (0);
	return (result);
}

void	env_var_transform(char **result, t_process *prcs)
{
	int		i;
	t_envp	*node;
	char	*temp;

	i = 0;
	temp = ft_strdup(result[i]);
	free(result[i]);
	node = ft_envpfind(prcs->envp, (result[i] + 1));
	if (ft_strncmp(temp, "$?", 3) == 0)
		result[i] = ft_itoa(prcs->envp->status);
	else if (node != NULL)
		result[i] = ft_strdup(node->value);
	else if (ft_strncmp(temp, "$PWD", 5) == 0)
		result[i] = ft_strdup(prcs->senvp.pwd);
	else if (ft_strncmp(temp, "$OLDPWD", 7) == 0)
		result[i] = ft_strdup(prcs->senvp.oldpwd);
	else if (ft_strncmp(temp, "$HOME", 6) == 0)
		result[i] = ft_strdup(prcs->senvp.home);
	else if (ft_strncmp(temp, "$", 2) == 0)
		result[i] = ft_strdup("$");
	else
		*result = ft_strdup("");
	free(temp);
}

void	expand_env_string(char **line, t_process *prcs)
{
	char	*temp;
	int		i;
	char	**result;

	i = 1;
	if (ft_strchr(*line, '$') == 0)
		return ;
	else
	{
		result = env_split(*line);
		temp = *line;
		while (i < ft_atoi(result[0]) + 1)
		{
			if (result[i][0] == '$')
				env_var_transform(&result[i], prcs);
			i++;
		}
		*line = make_one_line(result, -1, 0);
		free_split(result);
		free(temp);
		temp = NULL;
	}
}
