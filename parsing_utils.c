/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/17 21:16:53 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"
#include "parsing.h"

void print_list(t_tmp_list *list)
{
	t_tmp_node *head;
	head = list->front;
	int i = 0;

	while(head != NULL)
	{
		printf(" \"%s\" ",head->token);
		head = head->next;
	}
}

void	clear_list(t_tmp_list *list)
{
	t_tmp_node *head;
	t_tmp_node *temp;
	head = list->front;
	int i = 0;

	while(list->size > 0)
	{
		del_front(list);
	}
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
			++len;
	}
	return (len);
}

char	*put_token(char *str)
{
	int		len;
	int		i;
	char	*str2;

	// if (str[0] == '\'' || str[0] == '\"')
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

void	token_split(char *line, t_tmp_list *tmp_list)
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
					add_rear(tmp_list, cmdline, 0);
				}
				line += (int)ft_strlen(cmdline);
				if (!*line)
					break;
			}
	}
	free(cmdline);
}
