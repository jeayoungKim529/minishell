
#include "minishell.h"
#include "parsing.h"

void	add_token_list(t_token_list *list, char *token, t_token_type type)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	if (new_node == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	new_node->token = ft_strdup(token);
	if(new_node->token == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	if (type != 9)
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
		if (tmp != NULL)
			free(tmp);
	}
	else
		free(list->front);
	list->size--;
}
void	add_command_list(t_command_list *list)
{
	t_command_node	*new_node;

	new_node = (t_command_node *)malloc(sizeof(t_command_node));
	if (new_node == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}

	new_node->next = NULL;
	new_node->prev = NULL; 
	// new_node->
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
}

void	del_command_list(t_command_list *list)
{
	t_command_node	*tmp;

	if (list->size > 1)
	{
		tmp = list->front;
		list->front = list->front->next;
		list->front->prev = NULL;
		if (tmp != NULL)
			free(tmp);
	}
	else
		free(list->front);
	list->size--;
}