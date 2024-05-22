/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:29:20 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 15:43:17 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	execute_command(t_command_list *list)
// {
// 	// //리다이렉션에 필요한 fd값 저장
// 	// init_info_fd();
// 	// //명령어의 앞뒤로 pipe 여부
// 	// check_pipe();
// 	// 
// 	//builtin 명령어 여부
// 	if (check_builtin_comment() == 1)
// 	{
// 		//->yes : builin 명령어 처리 => END
// 		execute_builtin();
// 	}
// 	else
// 	{
// 		//->no : fork() 자식 프로세스 생성
// 		//builtin 함수 여부
// 		//execve 함수 실행 후 종료
// 			execve();
// 		//부모 wait
// 		wait();
// 	}
// 	//pipe 여부 확인
// 		//->yes : 반복
// 		//->no : => END
// }

void	execute_commands(t_process *prcs, t_command_list *list)
{
	t_command_node	*cur;

	// if (!list)
	// 	ft_error();
	cur = list->front;
	//prcs->io.prev = dup(0);
	while (cur)
	{
		prcs->cmd = merge_command(prcs, cur->cmd_list);
		prcs->token_list = cur->cmd_list;
		if (check_builtin_command(prcs->cmd) == 1)
			execute_builtin(prcs);
		else
		{
			init_prcs();
			open_pipe();
			set_redirection();
			close_pipe();
				//free(prcs->path);
		}
		free(prcs->cmd);
		cur = cur->next;
	}
}
