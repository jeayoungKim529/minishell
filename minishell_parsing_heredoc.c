/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:40:07 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/14 10:36:01 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	ft_pipex_strlen(char *s)
{
	unsigned int	len;

	len = 0;
	if (s == NULL) // 임시
		return (0); // 임시
	while (*s++ && *s != '\n')
		len++;
	return (len + 1);
}


void	set_heredoc(t_command_node	*node, int i)
{
	int j;
	t_token_node	*r_token;
	
	j = -1;
	r_token = node->redir_list->front;

	while (++j < node->redir_list->size)
	{
		if (r_token->type == TOKEN_IN_APPEND)
			set_heredoc_file(&r_token, set_heredoc_path(r_token, ft_itoa(i), ft_itoa(j), 0));
		r_token = r_token->next;
	}
}

void	set_command(t_command_node	*node, t_process *prcs)
{
	int	i;
	t_token_node	*c_token;
	char            *temp;

	i = -1;
	c_token = node->cmd_list->front;

	while (++i < node->cmd_list->size)
	{
		if (c_token->type == TOKEN_COMMAND)
		{
			if (ft_strchr(c_token->token, '$') != 0)
			{

			temp = c_token->token;
			c_token->token = get_parse_command(temp, prcs);
			free(temp);
			temp = NULL;
			}
		} 
		c_token = c_token->next;
	}
}

void parse_command_list(t_command_list *list, t_process *prcs)
{
	int				i;
	int				j;
	int				count;
	t_command_node	*node;

	i = -1;
	count = 0;
	node = list->front;
	while (++i < list->size)
	{
		set_command(node, prcs);
		set_heredoc(node, i);
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
	int				status;
	int				heredoc_fd;

	node = *token_node;
	if (path == NULL)// 에러함수로 대체
		ft_error_parse(2, "heredoc path error");
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)// 에러함수로 대체
		ft_error_parse(2, "heredoc error");

	heredoc_fd = fork();
	// printf("heredoc_fd: %d\n",heredoc_fd);
	if (heredoc_fd != 0)
		signal_off();
	if (heredoc_fd == 0)
		heredoc_readline(fd, node->token);
	wait(&status);
	// printf("whodo\n");
	builtin_signal_func(); 
	// TODO 히어독 종료 코드 설정
	if (WIFEXITED(status))
	printf("WIFEXITED %d\n",WEXITSTATUS(status));
	free (node->token);
	node->token = path;
	close(fd);
}

char	*expand_env(char *str, int check)
{
	if (check == 0)
		return (str);
	return (0);
}

// char	*check_end_text(char * token)
// {
	
// }

void	heredoc_readline(int fd, char *token)
{
	char	*str;
	int		check;
	char	*end_text;


	check = 0;
	
	heredoc_signal_func();
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, token, ft_pipex_strlen(str)) == 0 || !str)
			break ;
		write (fd, "\n", 1);
		write (fd, expand_env(str, check), ft_strlen(str));
		if (str != NULL)
			free (str);
	}
	if (str)
		free(str);
	// builtin_signal_func();
	exit(0);
}
