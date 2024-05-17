/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_open.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:31:49 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/14 20:25:10 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_minishell(t_info *info)
{
	// //리다이렉션에 필요한 fd값 저장
	// init_info_fd();
	// //명령어의 앞뒤로 pipe 여부
	// check_pipe();
	// 
	//builtin 명령어 여부
	if (check_builtin_comment() == 1)
	{
		//->yes : builin 명령어 처리 => END
		builtin();
	}
	else
	{
		//->no : fork() 자식 프로세스 생성
		//builtin 함수 여부
		//execve 함수 실행 후 종료
			execve();
		//부모 wait
		wait();
	}
	//pipe 여부 확인
		//->yes : 반복
		//->no : => END
}
