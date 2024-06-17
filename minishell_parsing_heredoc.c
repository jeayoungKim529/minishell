/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_heredoc.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:40:07 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/17 16:51:15 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

size_t	p_strlen(char *s)
{
	unsigned int	len;

	len = 0;
	if (s == NULL)
		return (0);
	while (*s++ && *s != '\n')
		len++;
	return (len + 1);
}
int	set_redir(t_token_node **node, t_process *prcs)
{
	char	*temp;

		temp = get_parse_command((*node)->token, prcs, 1);
		if (ft_strlen(temp) == 0)
		{
			free(temp);
			temp = NULL;
			return (1);
		}
		free((*node)->token);
		(*node)->token = temp;
		temp = 0;
	return (0);
}

int	set_heredoc(t_command_node	*node, int i, int j, t_process *prcs)
{
	t_token_node	*r_token;
	char			*path;
	char			*num;
	char			*name;

	r_token = node->redir_list->front;
	while (++j < node->redir_list->size)
	{
		if (r_token->type == TOKEN_IN_APPEND)
		{
			num = ft_itoa(i);
			name = ft_strjoin(num, "-");
			path = set_heredoc_path(num, ft_itoa(j), name);
			if (path == NULL)
				ft_error_parse(2, "heredoc path error");
			set_heredoc_file(&r_token, path, prcs);
		}
		else
		{
			if (set_redir(&r_token, prcs) == 1)
				return (1);
		}
		r_token = r_token->next;
	}
	return (0);
}

char	*set_heredoc_path(char *i, char *j, char *name)
{
	char	*temp;
	char	*path;

	temp = ft_strjoin(name, j);
	free(name);
	name = ft_strjoin(temp, ".txt");
	free(temp);
	path = ft_strjoin("./.temp/", name);
	if (access(path, F_OK) == 0)
	{
		while (42)
		{
			if (access(path, F_OK) == -1)
				break ;
			temp = ft_strjoin("0", name);
			free(name);
			name = temp;
			free(path);
			path = ft_strjoin("./.temp/", name);
		}
	}
	free(name);
	free(i);
	free(j);
	return (path);
}

void	set_heredoc_file(t_token_node **token_node, char *path, t_process *prcs)
{
	t_token_node	*node;
	int				fd;
	int				status;
	int				heredoc_fd;

	node = *token_node;
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		ft_error_parse(2, "heredoc error");
	heredoc_fd = fork();
	if (heredoc_fd != 0)
		signal_off();
	if (heredoc_fd == 0)
		heredoc_readline(fd, node->token, prcs, 1);
	wait(&status);
	builtin_signal_func();
	if (WIFEXITED(status))
		prcs->envp->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		prcs->envp->status = WIFSIGNALED(status) + 128;
	free (node->token);
	node->token = path;
	close(fd);
}

void	heredoc_readline(int fd, char *token, t_process *prcs, int check)
{
	char	*str;
	char	*end_text;

	if (ft_strchr(token, '\"') != NULL || ft_strchr(token, '\'') != NULL)
		check = 0;
	end_text = get_parse_command(token, prcs, 0);
	heredoc_signal_func();
	while (1)
	{
		str = readline("> ");
		if (ft_strncmp(str, end_text, p_strlen(end_text) + 1) == 0 || !str)
			break ;
		write (fd, expand_env(&str, check, prcs), ft_strlen(str));
		write (fd, "\n", 1);
		if (str != NULL)
			free (str);
	}
	if (str)
		free(str);
	str = NULL;
	if (end_text)
		free (end_text);
	end_text = NULL;
	exit(0);
}
