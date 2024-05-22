/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/22 11:57:11 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"
#include "parsing.h"

void print_command_list(t_command_list *list)
{
	t_command_node *head;
    head = list->front;
    int i = 0;

    while(i <= list->size)
    {
        printf("list[%d]\n", i);
		printf("redir_list = ");
		print_list(head->redir_list);
		printf("cmd_list = ");
		print_list(head->cmd);
        head = head->next;
		i++;
    }
}

void print_list(t_token_list *list)
{
	t_token_node *head;
	head = list->front;
	int i = 0;

	while(head != NULL)
	{
		printf(" \"%s\" ",head->token);
		head = head->next;
	}
}

void	clear_list(t_token_list *list)
{
	t_token_node *head;
	t_token_node *temp;
	head = list->front;
	int i = 0;

	while(list->size > 0)
	{
		del_token_list(list);
	}
}
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
	else if (str[0] == '\"' || str[0] == '\'')
		len = parse_quotes(str);
	else
	{
		while (str[len] && str[len] != ' ' && str[len] != '|' && str[len] != '>' && str[len] != '<')
			len ++;
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
	if (str2[0] == '\0')
	{
		free(str2);
		return (0);
	}
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
		return (STDIN_REDIRECT);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (STDIN_APPEND);
	else if (ft_strncmp(str, ">", 2) == 0)
		return (STDOUT_REDIRECT);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (STDOUT_APPEND);
	else
		return (TOKEN_COMMAND);
}

void	token_split(char *line, t_token_list *tmp_list)
{
	//"" '' 짝수개인지 확인
	// 리다이렉션 이후 파일이름 있는지
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
					// free(cmdline);
				}
				line += (int)ft_strlen(cmdline);
				if (!*line)
					break;
			}
	}
	// free(cmdline);
}
