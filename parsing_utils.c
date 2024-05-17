/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:26:23 by jimchoi           #+#    #+#             */
/*   Updated: 2024/05/17 16:11:21 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

void print_list(t_tmp_list *list)
{
	t_tmp_node *head;
	head = list->front;
	int i = 0;

	while(i < list->size)
	{
		int temp = head->idx;
		printf("%s -> ",head->token);
		if (head -> next != NULL)
			head = head->next;
		if (head->idx != temp || head -> next == NULL)
			printf("\n");
		i++;
	}
}

char	*put_token(char const *str)
{
	size_t	len;
	size_t	i;
	char	*str2;

	len = 0;
	i = 0;
	while (str[len] && str[len] != ' ' && str[len] != '|')
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
	if (str2[0] == '\0')
	{
		free(str2);
		return (0);
	}
	return (str2);
}

void	token_split(char *line)
{
	//"" '' 짝수개인지 확인
	// 리다이렉션 이후 파일이름 있는지
	int i = 0;
	char flag = '\0';

	while (line[i])
	{
		if(flag == '\0')
		{
			while (line[i] && line[i] == ' ')
				i++;

			if (line[i] == '|' && line[i])
				printf("pipe!\n");// pipe_check();
			if (line[i])
			{
				printf("token = |%s| \n",put_token(line + i));
				i += ft_strlen(put_token(line + i));
			}
		}
		i++;
	}
}