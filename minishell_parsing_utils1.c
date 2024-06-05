/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/05 21:55:17 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"


void check_leaks(void)
{
	system ("leaks minishell");
}



int	parsing(t_command_list	*cmd_list, char *line)
{
	t_token_list token_list;

	token_list.size = 0;
	cmd_list->size = 0;
	
    if (!cmd_list)
	{
		free_command_list(cmd_list);
	}
	if (token_split(line, &token_list))
	{
		clear_list(&token_list);
		return (1);
	}
		// print_list(&token_list);
	if (make_command_list(&token_list, cmd_list))
	{
		clear_list(&token_list);
		free_command_list(cmd_list);
		return (1);
	}
	// if (cmd_list->front->cmd_list->size == 0 && \
	// cmd_list->front->redir_list->size == 0)
	// {
	// 	free_command_list(cmd_list);
    //     cmd_list = NULL;
	// }


	clear_list(&token_list);
	if(cmd_list != NULL)
	set_heredoc(cmd_list);

	return (0);
}

void readline_func(t_command_list *list, t_process *prcs)
{
    char *str;
	int fd;
	int status;
    while(1)
    {
    
        str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{
			if (parsing(list, str) == 1)
			{
				free(str);
				continue;
			}
		}
        else/* str = NULL 이라면 (EOF, cntl + D)*/
            break ;/* 반복문을 탈출해준다.*/
		add_history(str);
						// print_command_list(list);
		// if (list->)
		// execute_commands(prcs, list);
		free(str);
    }
    /* 함수종료 */
    // return(0);
    atexit(check_leaks);
}
