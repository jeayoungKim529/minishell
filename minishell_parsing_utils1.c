/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/12 21:31:16 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"

int parsing(t_command_list	*cmd_list, char *line, t_process *prcs);


// void check_leaks(void)
// {
// 	system ("leaks minishell");
// }



int	parsing(t_command_list	*cmd_list, char *line, t_process *prcs)
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
		//exit status : 258
		// prcs->envp->value = 258;
		return (1);
	}
		// print_list(&token_list);
	if (make_command_list(&token_list, cmd_list))
	{
		clear_list(&token_list);
		free_command_list(cmd_list);
		//exit_status : 258
		// prcs->envp->value = 258;
		return (1);
	}
	// if (cmd_list->front->cmd_list->size == 0 && \
	// cmd_list->front->redir_list->size == 0)
	// {
		// free_command_list(cmd_list);
        // cmd_list = NULL;
	// }


	// clear_list(&token_list);
	// // if(cmd_list != NULL)
	parse_command_list(cmd_list, prcs);
	print_command_list(cmd_list);


	return (0);
}

void readline_func(t_command_list *list, t_process *prcs)
{
    char *str;
	int fd;
    while(1)
    {
    
        str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{
			if (parsing(list, str, prcs) == 1)
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
		execute_commands(prcs, list, 0);
		free(str);
		str = NULL;
    }

    /* 함수종료 */
    // return(0);
    // atexit(check_leaks);
	exit(0);
}
