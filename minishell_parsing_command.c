/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 12:48:40 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/03 16:26:47 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "minishell_parsing.h"

int	is_meta(t_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_IN_APPEND 
		|| type == TOKEN_OUT_APPEND || type == TOKEN_IN_REDIRECT 
		|| type == TOKEN_OUT_REDIRECT)
		return (1);
	return (0);
}
size_t	ft_pipex_strlen(char *s)
{
	unsigned int	len;

	len = 0;
	while (*s++ && *s != '\n')
		len++;
	return (len + 1);
}
void	set_redirect_heredoc(t_token_node *token_node, t_command_node *cmd_node)
{
	char	*end_text;
	char	*str;
	int		fd;
	char	*heredoc_txt;

    heredoc_txt = ft_strjoin(token_node->next->token, ".txt");
	fd = open(heredoc_txt, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
	{
		printf("heredoc error\n");
		exit(1);
	} 
	// signal(SIGINT, handle_signal_heredoc);
	end_text = token_node->next->token;
	if (ft_strchr(end_text, '\"') == 0)
	{
		// 환경변수 치환하기
		while (1)
		{
			str = get_next_line(0);
			if (!str)
			{
				printf("heredoc error\n");
				exit(1);
			}
			if (ft_strncmp(str, end_text, ft_pipex_strlen(str)) == 0)
				break ;
			write(fd, str, ft_strlen(str));
			free(str);
		}
	}
	// else
	// {
			// 환경변수 치환 안하기
	// }
	add_token_list(cmd_node->redir_list, heredoc_txt, token_node->type);
	close(fd);
}

int	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node)
{
	int count;

	count = 1;
	if (token_node->next == NULL || is_meta(token_node->next->type) )
	{
		printf("syntax error near unexpected token \n");
		exit(1);
	}
	if (token_node->type == TOKEN_IN_APPEND)
	{
		set_redirect_heredoc(token_node, cmd_node);
	}
	else
		add_token_list(cmd_node->redir_list, token_node->next->token, token_node->type);
	return (2);
}
int set_pipe(t_token_node *token_node, t_command_node **cmd_node, t_command_list *cmdline)
{
	if ((token_node->prev != NULL && is_meta(token_node->prev->type)) || token_node->next == NULL)
	{
		printf("syntax error near unexpected token |\n");
		exit(1);
	}
	add_command_list(cmdline);
	*cmd_node = cmdline->rear;
	return (1);
}

void	make_command_list(t_token_list *token_list, t_command_list *cmdline)
{
	t_command_node	*cmd_node;
	t_token_node	*node;
	int				i;
	
	i = 0;
	node = token_list->front;
	if (token_list->size == 1 && node->type == TOKEN_PIPE)
	{
		printf("syntax error near unexpected token meta\n");
		exit(1);
	}
	add_command_list(cmdline);
	cmd_node = cmdline->rear;
	while (i < token_list->size)
	{
		if (node->type == TOKEN_PIPE )
			i += set_pipe(node, &cmd_node, cmdline);
		else if (node->token[0] == '>' || node->token[0] == '<')
		{
			i += set_redirect_list(node, cmd_node);
			node = node->next;
		}
		else
			i += add_token_list(cmd_node->cmd_list, node->token, node->type);
		node = node->next;
	}
}

