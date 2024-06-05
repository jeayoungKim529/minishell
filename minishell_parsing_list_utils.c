/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_list_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jimchoi <jimchoi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:40:02 by jimchoi           #+#    #+#             */
/*   Updated: 2024/06/05 16:44:45 by jimchoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include "minishell_parsing.h"

int	add_token_list(t_token_list *list, char *token, t_token_type type)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == NULL)
		ft_error_parse(1, "malloc error");
	new_node->token = ft_strdup(token);
	if(new_node->token == NULL)
		ft_error_parse(1, "malloc error");
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL; 
	if (list->size == 0)
	{
		list->front = new_node;
		list->rear = new_node;
	}
	else
	{
		list->rear->next = new_node;
		new_node->prev = list->rear;
		list->rear = new_node;
	}
	list->size++;
	return (1);
}

void	del_token_list(t_token_list *list)
{
	t_token_node	*tmp;

	if (list->size > 1)
	{
		tmp = list->front;
		list->front = list->front->next;
		list->front->prev = NULL;
		free(tmp->token);
		// if (tmp != NULL)
		free(tmp);
	}
	else
	{
		free(list->front->token);
		free(list->front);
	}
	list->size--;
}
int	add_command_list(t_command_list *list)
{
	t_command_node	*new_node;
	t_token_list	*cmd_list;
	t_token_list	*redir_list;

	new_node = (t_command_node *)malloc(sizeof(t_command_node));
	cmd_list = (t_token_list *)malloc(sizeof(t_token_list));
	redir_list = (t_token_list *)malloc(sizeof(t_token_list));
	if (new_node == NULL || cmd_list == NULL || redir_list == NULL)
		ft_error_parse(1, "malloc error");

	new_node->next = NULL;
	new_node->prev = NULL; 
	new_node->cmd_list = cmd_list;
	new_node->redir_list = redir_list;
	cmd_list->size = 0;
	redir_list->size = 0;
	if (list->size == 0)
	{
		list->front = new_node;
		list->rear = new_node;
	}
	else
	{
		list->rear->next = new_node;
		new_node->prev = list->rear;
		list->rear = new_node;
	}
	list->size++;
	return (1);
}

void	del_command_list(t_command_list *list)
{
	t_command_node	*tmp;

	if (list->size > 1)
	{
		tmp = list->front;
		list->front = list->front->next;
		list->front->prev = NULL;
		clear_list(tmp->cmd_list);
		clear_list(tmp->redir_list);
		free(tmp->cmd_list);
		free(tmp->redir_list);
		free(tmp);
	}
	else
	{
		clear_list(list->front->cmd_list);
		clear_list(list->front->redir_list);
		free(list->front->cmd_list);
		free(list->front->redir_list);
		free(list->front);
	}
	list->size--;

}



void print_command_list(t_command_list *list)
{
	t_command_node *head;
    head = list->front;
    int i = 0;

        printf("total list size :%d\n\n", list->size);
		// if (head == NULL)
		// 	return;
		// if (head->cmd_list == 0 || head->redir_list == 0)
		// 	return ;
		// if (head->cmd_list->size == 0 || head->redir_list->size == 0)
		// 	return ;
		printf("========================\n");
    while(i < list->size)
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


void print_list(t_token_list *list)
{
	t_token_node *head;
	head = list->front;
	int i = 0;


    printf("size = %d\n", list->size);
	if (list->size == 0)
		return ;
	while(i < list->size)
	{
		printf(" |%s| ",head->token);
		printf("type :%u ",head->type);
		head = head->next;
		printf("->");
		i++;
	}
	printf("\n");
}

void	clear_list(t_token_list *list)
{
	t_token_node *head;
	t_token_node *temp;
	head = list->front;
	
	while(list->size != 0)
	{
		del_token_list(list);
	}
}

void free_command_list(t_command_list *command_list)
{
    t_command_node *curr;
	t_command_node *next;
	int i = 0;

    curr = command_list->front;
    while (command_list->size != 0)
    {
        del_command_list(command_list);
    }

    // free(command_list);
}