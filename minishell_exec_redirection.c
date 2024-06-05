/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_redirection.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:08:24 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/05 19:12:28 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

void	set_single_redirection(t_process *prcs)
{
	if (prcs->file.in != -1)
		if (dup2(prcs->file.in, 0) == -1) // 입력 파일이 있는 경우
			ft_error_exec(prcs, strerror(errno));
	if (prcs->file.out != -1)
	{
		prcs->prevfd = dup(1);
		if (dup2(prcs->file.out, 1) == -1) // 출력 파일이 있는 경우
			ft_error_exec(prcs, strerror(errno));
		close(prcs->file.out);
	}
}

void	set_redirection_read(t_process *prcs, t_token_node *cur)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cur->type == TOKEN_IN_REDIRECT)
	{
		tmp_fd = open(cur->token, O_RDONLY);
		if (tmp_fd < 0)
			ft_error_exec(prcs, strerror(errno));
	}
	else if (cur->type == TOKEN_IN_APPEND)
	{
		tmp_fd = open(cur->token, O_RDONLY);
		if (tmp_fd < 0)
			ft_error_exec(prcs, strerror(errno));
	}
	if (tmp_fd > -1)
	{
		close(prcs->file.in);
		prcs->file.in = tmp_fd;
	}
	cur = cur->next;
}

void	set_redirection_write(t_process *prcs, t_token_node *cur)
{
	int	tmp_fd;

	tmp_fd = -1;
	if (cur->type == TOKEN_OUT_REDIRECT || cur->type == 3)
	{
		tmp_fd = open(cur->token, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		if (tmp_fd == -1)
			ft_error_exec(prcs, strerror(errno));
	}
	else if (cur->type == TOKEN_OUT_APPEND || cur->type == 5)
	{
		tmp_fd = open(cur->token, O_WRONLY | O_CREAT | O_APPEND, 0666);
		if (tmp_fd == -1)
			ft_error_exec(prcs, strerror(errno));
	}
	if (tmp_fd > -1)
	{
		close(prcs->file.out);
		prcs->file.out = tmp_fd;
	}
}

void	set_redirection(t_process *prcs, t_token_list *list)
{
	t_token_node	*cur;

	cur = list->front;
	while (cur)
	{
		if (cur->type == TOKEN_IN_REDIRECT || cur->type == TOKEN_IN_APPEND)
			set_redirection_read(prcs, cur);
		else if (cur->type == TOKEN_OUT_REDIRECT || cur->type == TOKEN_OUT_APPEND)
			set_redirection_write(prcs, cur);
		cur = cur->next;
	}
}
