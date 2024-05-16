#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum)
{
    if (signum != SIGINT)
        return;
    printf("ctrl + c\n");
    rl_on_new_line();
    rl_replace_line("", 1);
    rl_redisplay();
}

int main(void)
{
    int ret;
    char *line;
	int i=0;

    signal(SIGINT, handler);
    while (i++ < 10)
    {
        line = readline("input> ");
        if (line)
        {
            if (ret)
                printf("output> %s\n", line);
            add_history(line);
            free(line);
            line = NULL;
        }
        else
        {
            printf("ctrl + d\n");
        }
    }
    return (0);
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