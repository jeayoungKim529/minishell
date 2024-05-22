#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

#include "minishell.h"
#include "parsing.h"



// void check_leaks(void)
// {
// 	system ("leaks minishell");
// }
void	set_redirect_list(t_token_node *token_node, t_command_node *cmd_node)
{
	if (token_node->token[0] == '>')
	{
		if (token_node->next == NULL)
		{
			printf("> error\n");
			exit(1);
		}
		if (token_node->type == STDOUT_APPEND)
		{
			// >> 처리
		}
		add_token_list(cmd_node->redir_list, token_node->next->token, token_node->type);
		token_node = token_node->next->next;
		//파일 열어보기
	}
	else
	{
		if (token_node->next->type == STDIN_APPEND)
		{
			// << 처리
		}
		add_token_list(cmd_node->redir_list, token_node->token, token_node->next->type);
		token_node = token_node->next->next;
	}
}

void set_quote (t_token_node *token_node, t_command_node *cmd_node, char *token)
{
	int	start;
	char	quote;
	// char	*quote;

	start = 0;
	while (*token != NULL)
	{
		if (*token == '\"' || *token == '\'')
			break;
	}
	quote = *token;
	while (token != ft_strrchr(token, quote))
	{
		
	}
}

make_command_list(t_token_list *token_list, t_command_list *cmd_list)
{
	int	i;
	t_token_node	*node;
	t_command_node    *cmd_node;

	i = -1;
	node = token_list->front;
	cmd_node = cmd_list->front;
	while(++i <= token_list->size)
	{
		if (node->token[0] == '|')
			add_command_list(cmd_node);//다음 커맨드노드 생성 후 다음 노드로
		else if (node->token[0] == '>' || (node->next != NULL && node->token[0] == '<'))
		{
			set_redirect_list(node, cmd_node);
			i++;
			// < | TOKEN_VARIABLE
			// | > 가능함
		}
		else
		{
			// if (ft_strchr(node->token, '\"') != 0 || ft_strchr(node->token, '\''))
			// {
			// 	// 가장 바깥 따옴표 지우기
			// 	if (ft_strchr(node->token, '\"') != 0 || ft_strchr(node->token, '\'') != 0)
			// 		// set_quote(node, cmd_node);
			// 	if (ft_strchr(node->token, '$') != 0 && node->type != TOKEN_SINGLE_QUOTE)
			// 		node->type = TOKEN_VARIABLE;

			// }
			add_token_list(cmd_node->cmd, node->token, node->type);// 커맨드 저장 다음노드 , 따옴표 제거
		}
	}
	// clear_list(&token_list);
}

void parsing(t_command_list	*list, char *line)
{
	// t_tmp_list token_list;
	t_token_list token_list;
	t_command_list cmd_list;
	token_list.size = 0;
	cmd_list.size = 0;
	char flag = '\0';
	
	token_split(line, &token_list);
	if (token_list.size > 0)
	{
		print_list(&token_list);
		clear_list(&token_list);
	}
	// make_command_list(&token_list, &cmd_list);


    // atexit(check_leaks);
}

int main(void)
{
/* readline함수의 리턴값을 저장하기위해 임의로 포인터를 하나 선언한다 */
    char *str;
/* 무한루프를 돌리면서 readline();함수를 반복적으로 호출할 것이다 */
    while(1)
    {
        /* readline함수가 호출되면 인자(prompt : )를 터미널에 출력하고 저장할 라인을 입력받는다 */
        str = readline("prompt : ");/* read함수는 저장한 문자열의 메모리주소를 반환한다 */
        if (str)/* 입력이 된다면 (주소가 존재한다면) */
		{

            printf("%s\n", str);/* 주소안에 문자열을 출력해보자 */
			parsing(0, str);
		}
        else/* str = NULL 이라면 (EOF, cntl + D)*/
            break ;/* 반복문을 탈출해준다.*/
	/* add_history에 저장된 문자열은 up & down 방향키를 이용해 확인할수있다 */
        add_history(str);
	/* 라인은 힙메모리에 저장되기때문에 다 사용한 메모리는 할당을 해제해줘야한다 */
        if (str != NULL)
			free(str);
    }
    /* 함수종료 */
    return(0);
}



/*
readline으로 한 줄씩 읽기
line = readline("minishell>");
if (!line)
    break;
if (!*line) // 입력이 없을 때
    continue;
history 추가

파싱()
{
    | 별로  나눠서 cmd node에 저장
    나눠진 cmd str을 ' ' 기준으로 split
    빌트인인지 아닌지 체크
    히어독인지 체크
}
*/


/*

컴파일러이론 (덜필요함)


오토마타

언어학적으로 트리구조로 만들어야함
문법적으로 트리구조로 만들어야함

왜 트리구조로 만들어야하는가?
bnf rule


리드라인은 재영이가 해
리드라인은 히스토리를 저장해줌 재영이가 해

빌트인 함수는 재영이가 해 execv랑 똑같은 구조로 하면 편하다
execv



명령어를 리스트로 줄지 2차원배열로 깎아서 줄지

리다이랙션


pipeline 
명령어 |



<< end cat <a > b >> c

a 랑 c만

리다이렉션 처리 어려움 연결리스트에서

토큰 하나하나 연결리스트에 넣어서? 
메타캐릭터 문자 하나가 의미를 가지는 세미콜론 따옴표  < > $(잘 안쳐줌)
$는 재영이가 해

cat-ls 해도 잘됨

cat-ls 안되어야함

메타캐릭터 기준으로 잘라서 재영이 주기



신텍스에러 띄우기
연결리스트는 힘듬
파싱부에서도 신텍스에러 처리를 해줘야함
미리 생각할것

bnf룰을 먼저 짠다면 체크하기 쉽다

커맨드라인 재영이가 해

:= ~로 정의합니다

커맨드라인 := 커맨드라인
커맨드라인 := 커맨드리스트
커맨드리스트 := 파이프라인 := 파이프라인 ["|" 파이프라인 ]
파이프라인 := 커맨드 := 커맨드 [">" 파일이름] ["<" 파일이름] [">>" 파일이름] ["<<" 파일이름]
파이프라인 := 커맨드 := 커맨드 리다이렉션 
리다이렉션 := (< | << | > | >>) & 파일명

신텍스에러 잡는법 

bnf룰에 따라 없는게 들어오면 에러

| 가 나오면 하나의 파이프라인이 완성되었구나

더이상 만들게 없고 커맨드라인을 다 읽으면 ok
실행부가 해
아니면 다 프리해주고 신텍스에러

1. 리스트? 2차원배열?  자료 주고받기
2. 확장 환경변수 $PATH 
3. 와일드카드 *



리드라인
허


list로 만들어서 넘김
' ' 을 기준으로 나눔
각 노드에 타입을 저장해놓음


*/