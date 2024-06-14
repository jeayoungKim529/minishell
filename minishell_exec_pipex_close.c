/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_pipex_close.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:03:09 by jeakim            #+#    #+#             */
/*   Updated: 2024/06/12 19:44:41 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"
#include "minishell_parsing.h"

void	execute_wait(t_process *prcs, t_command_list *list, int flag)
{
	int	i;
	int	status;

	i = 0;
	while (flag == 0 && i < list->size && list->front->cmd_list->size > 0)
	{
		if (wait(&status) == -1)
			exit(EXIT_FAILURE);
		printf("WIFEXITED : %d\n",WIFEXITED(status));
        printf("WEXITSTATUS : %d\n",WEXITSTATUS(status));
        printf("WIFSIGNALED : %d\n",WIFSIGNALED(status));
		if (WIFEXITED(status))
			prcs->envp->status = WIFEXITED(status);
		else if (WEXITSTATUS(status))
			prcs->envp->status = WEXITSTATUS(status);
		// else 
		if (WIFSIGNALED(status))
			prcs->envp->status = WIFSIGNALED(status) + 128;
		printf("stats:%d\n", prcs->envp->status);
		i++;
	}
}

void	ft_unlink(t_process *prcs, t_command_list *list)
{
	t_token_node	*cur;

	if (!list || !list->front || !list->front->redir_list || \
		list->front->redir_list->size <= 0)
		return ;
	cur = list->front->redir_list->front;
	while (cur)
	{
		if (cur->type == TOKEN_OUT_APPEND)
			unlink(cur->token);
		cur = cur->next;
	}
}

void	finish_commands(t_process *prcs, t_command_list *list, int flag)
{
	execute_wait(prcs, list, flag);
	free_path(prcs);
	ft_unlink(prcs, list);
	builtin_signal_func();
}
