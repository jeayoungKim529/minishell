/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:36 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/04 18:19:27 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"
#include "minishell_exec.h"


void check_leaks(void)
{
	system ("leaks minishell");
}



void parsing(t_command_list	*cmd_list, char *line)
{
	t_token_list token_list;
	token_list.size = 0;
	cmd_list->size = 0;
	char flag = '\0';
	
	token_split(line, &token_list);
	// 	print_list(&token_list);
	make_command_list(&token_list, cmd_list);
	clear_list(&token_list);
	set_heredoc(cmd_list);
	if(cmd_list->size > 0)
	{
		printf( "cmd_list : ");
		print_command_list(cmd_list);
		free_command_list(cmd_list);
	}


}

void readline_func(t_command_list *list, t_process *prcs)
{
    char *str;
    while(1)
    {
    
        str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{

            printf("%s\n", str);/* 주소안에 문자열을 출력해보자 */
			parsing(list, str);
		}
        else/* str = NULL 이라면 (EOF, cntl + D)*/
            break ;/* 반복문을 탈출해준다.*/
	/* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
        add_history(str);
        if (str != NULL)
			free(str);
		// execute_commands(prcs, list);
    }
    /* 함수종료 */
    // return(0);
    atexit(check_leaks);
}
