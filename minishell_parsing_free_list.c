/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_free_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 17:20:04 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/15 13:55:04 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_parsing.h"

void	clear_list(t_token_list *list)
{
	t_token_node	*head;

	head = list->front;
	while (list->size != 0)
		del_token_list(list);
}

void	free_command_list(t_command_list *command_list)
{
	t_command_node	*curr;
	int				i;

	i = 0;
	curr = command_list->front;
	while (command_list->size != 0)
	{
		del_command_list(command_list, 0);
	}
}

void	print_list(t_token_list *list)
{
	t_token_node	*head;
	int				i;

	head = list->front;
	i = 0;
	printf ("size = %d\n", list->size);
	if (list->size == 0)
		return ;
	while (i < list->size)
	{
		printf (" |%s| ", head->token);
		printf ("type : %u", head->type);
		head = head->next;
		printf("->");
		i++;
	}
	printf("\n");
}

void	print_command_list(t_command_list *list)
{
	t_command_node	*head;
	int				i;

	head = list->front;
	i = 0;
	printf("total list size :%d\n\n", list->size);
	printf("========================\n");
	while (i < list->size)
	{
		printf("list[%d]\n", i);
		printf("----------------------------------\n");
		printf(" ㄴredir_list : ");
		print_list(head->redir_list);
		printf("----------------------------------\n");
		printf("ㄴcmd_list : ");
		print_list(head->cmd_list);
		printf("----------------------------------\n");
		printf("\n");
		head = head->next;
		i++;
	}
}
