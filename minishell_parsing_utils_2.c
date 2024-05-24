/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils_2.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/24 17:21:54 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"


int	is_white_space(char c)
{
	if (c ==' ' || c == '\t' || c == '\n' || c == '\v' || c == '\r')
        return (1);
    return (0);
}

int	is_meta(t_token_type type)
{
	if (type == TOKEN_PIPE ||
		type == STDIN_REDIRECT || type == STDOUT_REDIRECT || 
		type == STDIN_APPEND || type == STDOUT_APPEND)
        return (1);
    return (0);
}

int	parse_quotes(char *str)
{
	int		len;
	char	quote;

	printf("\n\nstr = %s\n\n", str);
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
	else if (str[len] == '\"' || str[len] == '\'')
				len += parse_quotes(str + len);
	else
	{
		while (str[len] && !is_white_space(str[len]) && str[len] != '|' && str[len] != '>' && str[len] != '<' && str[len] != '\"' && str[len] != '\'')
		{
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

// void quotes_check(char *line)
// {
// 	int in_single_quote;
// 	int in_double_quote;
// }

t_token_type set_token_type(char *str)
{
	if (*str == '|')
		return (TOKEN_PIPE);
	else if (ft_strncmp(str, "<", 2) == 0)
		return (STDIN_REDIRECT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (STDIN_APPEND);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (STDOUT_REDIRECT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (STDOUT_APPEND);
	else if (ft_strncmp(str, " ", 2) == 0)
		return (TOKEN_WHITESPACE);
	else
		return (TOKEN_COMMAND);
}

void	token_split(char *line, t_token_list *tmp_list)
{
	char *cmdline;
	int	wp;
	
	wp = 0;
	cmdline = 0;
	while (*line)
	{

		while (*line && *line == ' ')
		{
			line++;
			wp = 1;
		}
		if (wp)
			add_token_list(tmp_list, ft_strdup(" "), TOKEN_WHITESPACE);
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
		wp = 0;
	}
	if (cmdline)
		free(cmdline);
}
