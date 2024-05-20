
#include "minishell.h"
// #include "parsing.h"

// void	add_front(t_tmp_list *list, char *token, int idx)
// {
// 	t_tmp_node	*new_node;

// 	new_node = (t_tmp_node *)malloc(sizeof(t_tmp_node));
// 	new_node->token = token;
// 	new_node->idx = idx;
// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	if (list->size == 0)
// 	{
// 		list->front = new_node;
// 		list->rear = new_node;
// 	}
// 	else
// 	{
// 		new_node->next = list->front;
// 		list->front->prev = new_node;
// 		list->front = new_node;
// 	}
// 	list->size++;
// }

// void	add_rear(t_tmp_list *list, char *token, int idx)
// {
// 	t_tmp_node	*new_node;

// 	new_node = (t_tmp_node *)malloc(sizeof(t_tmp_node));
// 	new_node->token = token;
// 	new_node->idx = idx;
// 	// new_node->type = type;

// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	if (list->size == 0)
// 	{
// 		list->front = new_node;
// 		list->rear = new_node;
// 	}
// 	else
// 	{
// 		list->rear->next = new_node;
// 		new_node->prev = list->rear;
// 		list->rear = new_node;
// 	}
// 	list->size++;
// }

// void	del_front(t_tmp_list *list)
// {
// 	t_tmp_node	*tmp;

// 	if (list->size > 1)
// 	{
// 		tmp = list->front;
// 		list->front = list->front->next;
// 		list->front->prev = NULL;
// 		free(tmp->token);
// 		if (tmp != NULL)
// 			free(tmp);
// 	}
// 	else
// 		free(list->front);
// 	list->size--;
// }

// void	del_rear(t_tmp_list *list)
// {
// 	t_tmp_node	*tmp;

// 	if (list->size > 1)
// 	{
// 		tmp = list->rear;
// 		list->rear = list->rear->prev;
// 		list->rear->next = NULL;
// 		free(tmp);
// 	}
// 	else
// 		free(list->rear);
// 	list->size--;
// }

void	add_token_list(t_token_list *list, char *token, t_token_type type)
{
	t_token_node	*new_node;

	new_node = (t_token_node *)malloc(sizeof(t_token_node));
	new_node->token = token;
	// ft_strncmp(new_node->token, token, ft_strlen(token));
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