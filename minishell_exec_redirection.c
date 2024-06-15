/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:08:24 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/15 15:01:42 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

int	set_single_redirection(t_process *prcs)
{
	if (prcs->file.in != -1)
	{
		if (dup2(prcs->file.in, 0) == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	}
	else
		if (dup2(prcs->std_fd[0], 0) == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	if (prcs->file.out != -1)
	{
		if (dup2(prcs->file.out, 1) == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
		close(prcs->file.out);
	}
	else
		if (dup2(prcs->std_fd[1], 1) == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	return (1);
}

void	set_multi_redirection(t_process *prcs, int i)
{
	if (prcs->file.in == -1)
	{
		if (dup2(prcs->prevfd, 0) == -1)
			ft_error_exec_exit(prcs, strerror(errno), errno);
	}
	else if (dup2(prcs->file.in, 0) == -1)
		ft_error_exec_exit(prcs, strerror(errno), errno);
	if (prcs->file.out == -1)
	{
		if (i == prcs->t_cmd)
		{
			if (dup2(prcs->std_fd[1], 1) == -1)
				ft_error_exec_exit(prcs, strerror(errno), errno);
		}
		else
			if (dup2(prcs->fd[1], 1) == -1)
				ft_error_exec_exit(prcs, strerror(errno), errno);
	}
	else
	{
		if (dup2(prcs->file.out, 1) == -1)
			ft_error_exec_exit(prcs, strerror(errno), errno);
		close(prcs->file.out);
	}
}

int	set_redirection_read(t_process *prcs, t_token_node *cur)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cur->type == TOKEN_IN_REDIRECT)
	{
		tmp_fd = open(cur->token, O_RDONLY);
		if (tmp_fd == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	}
	else if (cur->type == TOKEN_IN_APPEND)
	{
		tmp_fd = open(cur->token, O_RDONLY);
		if (tmp_fd == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	}
	if (tmp_fd > -1)
	{
		close(prcs->file.in);
		prcs->file.in = tmp_fd;
	}
	return (1);
}

int	set_redirection_write(t_process *prcs, t_token_node *cur)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cur->type == TOKEN_OUT_REDIRECT || cur->type == 3)
	{
		tmp_fd = open(cur->token, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (tmp_fd == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	}
	else if (cur->type == TOKEN_OUT_APPEND || cur->type == 5)
	{
		tmp_fd = open(cur->token, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (tmp_fd == -1)
			return (ft_error_builtin(prcs, strerror(errno), errno));
	}
	if (tmp_fd > -1)
	{
		close(prcs->file.out);
		prcs->file.out = tmp_fd;
	}
	return (1);
}

int	set_redirection(t_process *prcs, t_token_list *list)
{
	t_token_node	*cur;

	cur = list->front;
	while (cur)
	{
		if (cur->type == TOKEN_IN_REDIRECT || cur->type == TOKEN_IN_APPEND)
		{
			if (set_redirection_read(prcs, cur) == -1)
				return (-1);
		}
		else if (cur->type == TOKEN_OUT_REDIRECT || \
			cur->type == TOKEN_OUT_APPEND)
			if (set_redirection_write(prcs, cur) == -1)
				return (-1);
		cur = cur->next;
	}
	return (1);
}
