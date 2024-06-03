/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_merge_command.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:02:51 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/30 17:58:52 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exec.h"

char	*check_envp(t_process *prcs, t_token_node *token_node) //환경변수($) 치환
{
	int		cnt;
	int		i;
	char	*s; //환경변수($) 전까지의 길이 담을 배열
	char	*res; //환경변수로 치환하여 실제 리턴될 값

	if (token_node->type != TOKEN_VARIABLE) //check_type : 환경 변수 여부
		return (token_node->token);
	cnt = 0;
	while (token_node->token[cnt] && token_node->token[cnt] != '$') //환경변수($) 전까지 길이 체크
		cnt++;
	s = (char *)ft_calloc(sizeof(char), cnt + 1); //환경변수($) 전까지의 길이 담을 배열 생성
	i = -1;
	while (++i < cnt)
		s[i] = token_node->token[i];
	res = ft_strjoin(s, ft_envpfind(prcs->envp, token_node->token + cnt));
	free(s);
	return (res);
}

char	**merge_command(t_process *prcs, t_token_list	*token_list) //연결리스트 명령어 -> 이차원배열 명령어
{
	t_token_node	*cur;
	char			**res; //이차원으로 명령어 저장할 배열
	int				i;

	cur = token_list->front;
	prcs->n_cmd = token_list->size;
	res = (char **)ft_calloc(sizeof(char *), prcs->n_cmd + 1);
	cur = token_list->front;
	i = 0;
	while (cur && i < prcs->n_cmd)
	{
		res[i] = check_envp(prcs, cur); //환경 변수 치환해서 저장
		i++;
		cur = cur->next;
	}
	return (res);
}
