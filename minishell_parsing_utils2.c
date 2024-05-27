/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/27 13:16:15 by jimchoi          ###   ########.fr       */
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
		printf("quote error\n str[0] = %s\n", ft_strchr(str, str[0]));
		exit(1);
	}
	if (quote == '\"')
	{
		// if (ft_strchr(str, '$') != 0)

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

int	get_cmd_length(char *str)
{
	int	len;

	len = 0;
	if (str[0] == '|' || str[0] == '>' || str[0] == '<')
	{
		if (str[0] == '>' && str[1] == '>' || str[0] == '<' && str[1] == '<')
			len = 2;
		else
			len = 1;
	}
	else
	{
		while (str[len] && str[len] != ' ' && str[len] != '|' && str[len] != '>' && str[len] != '<')
		{
			if (str[len] == '\"' || str[len] == '\'')
				len += parse_quotes(str);		
			len ++;
		}
	}
	return (len);
}

char	*put_token(char *str)
{
	int		len;
	int		i;
	char	*str2;

	
	len = get_cmd_length(str);
	i = -1;
 	str2 = (char *)malloc(sizeof(char) * (len + 1));
	if (!str2)
		return (0);
	while (++i < len)
		str2[i] = str[i];
	str2[i] = '\0';
	// if (str2[0] == '\0')
	// {
	// 	free(str2);
	// 	return (0);
	// }
	return (str2);
}

void quotes_check(char *line)
{
	int in_single_quote;
	int in_double_quote;
}

t_token_type set_token_type(char *str)
{
	if (*str == '|')
		return (TOKEN_PIPE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (TOKEN_IN_REDIRECT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (TOKEN_IN_APPEND);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (TOKEN_OUT_REDIRECT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (TOKEN_OUT_APPEND);
	else
		return (TOKEN_COMMAND);
}

void	token_split(char *line, t_token_list *tmp_list)
{
	char *cmdline;
	
	cmdline = 0;
	while (*line)
	{

		while (*line && *line == ' ')
			line++;
		if (*line)
		{
			cmdline = put_token(line);
			if (cmdline != NULL)
			{
				add_token_list(tmp_list, cmdline, set_token_type(cmdline));
				line += (int)ft_strlen(cmdline);
					free(cmdline);
					cmdline = 0;
			}
			if (!*line)
				break;
		}
	}
	if (cmdline)
		free(cmdline);
}