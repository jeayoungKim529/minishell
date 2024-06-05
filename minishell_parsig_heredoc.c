/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsig_heredoc.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:40:07 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/04 18:43:55 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

size_t	ft_pipex_strlen(char *s)
{
	unsigned int	len;

	len = 0;
	while (*s++ && *s != '\n')
		len++;
	return (len + 1);
}


void set_heredoc(t_command_list *list)
{
	int				i;
	int				j;
	int				count;
	t_command_node	*node;
	t_token_node	*token;

	i = -1;
	count = 0;
	node = list->front;
	while (++i < list->size)
	{
		j = -1;
		token = node->redir_list->front;
		while (++j < node->redir_list->size)
		{
			if (token->type == TOKEN_IN_APPEND)
			{
				set_heredoc_file(&token, set_heredoc_path(token, ft_itoa(i), ft_itoa(j), 0));
			} 
			token = token->next;
		}
		node = node->next;
	}
}

char *set_heredoc_path(t_token_node *node, char *i, char *j, char *temp)
{
	char	*file_name;
	char	*path;

	file_name = ft_strjoin(i, "-");
	temp = ft_strjoin(file_name, j);
	free(file_name);
	file_name = ft_strjoin(temp, ".txt");
	free(temp);
	path = ft_strjoin("./.temp/", file_name);
	if (access(path, F_OK) == 0)
	{
		while (42)
		{
			if (access(path, F_OK) == -1)
				break;
			temp = ft_strjoin("0",file_name);
			free(file_name);
			file_name = temp;
			free(path);
			path = ft_strjoin("./.temp/", file_name);
		}
	}
	free(file_name);
	free(i);
	free(j);
	return (path);
}

void	set_heredoc_file(t_token_node **token_node, char *path)
{
	t_token_node	*node;
	int				fd;

	node = *token_node;
	if (path == NULL)// 에러함수로 대체
	{
		printf("ft_strjoin error\n");
		exit (1);
	}
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)// 에러함수로 대체
	{
		printf("heredoc error\n");
		exit(1);
	}
	heredoc_readline(fd, node->token);
	free (node->token);
	node->token = path;
	close(fd);
}

void	heredoc_readline(int fd, char *end_text)
{
	char	*str;

// heredoc_signal_func();
	while (1)
	{
		str = readline("heredoc>");
		if (!str) // 에러함수로 대체
		{
			printf("heredoc error\n");
			exit(1);
		}
		if (ft_strncmp(str, end_text, ft_pipex_strlen(str)) == 0)
			break ;
		write (fd, str, ft_strlen(str));
		if (str != NULL)
			free (str);
	}
	free(str);
	signal_func();
}