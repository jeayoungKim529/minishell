
#include "minishell.h"
#include "minishell_parsing.h"

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
void	add_command_list(t_command_list *list)
{
	t_command_node	*node = malloc(sizeof(t_command_node));

	t_token_list *cmd2 = malloc(sizeof(t_token_list));
	t_token_list *redir2 = malloc(sizeof(t_token_list));

	if (node == NULL)
	{
		printf("malloc error\n");
		exit(1);
	}
	node->next = NULL;
	node->prev = NULL; 
	node->cmd_list = cmd2;
	node->redir_list = redir2;
	node->cmd_list->size = 0;
	node->redir_list->size = 0;
	if (list->size == 0)
	{
		list->front = node;
		list->rear = node;
	}
	else
	{
		list->rear->next = node;
		node->prev = list->rear;
		list->rear = node;
	}
	list->size++;
}
// void	add_command_list(t_command_list *list, t_command_node *node)
// {
// 	// t_command_node	*new_node;

// 	if (node == NULL)
// 	{
// 		printf("malloc error\n");
// 		exit(1);
// 	}
// 	node->next = NULL;
// 	if (list->size == 0)
// 	{
// 		node->next = NULL;
// 		node->prev = NULL; 
// 		list->front = node;
// 		list->rear = node;
// 	}
// 	else
// 	{
// 		list->rear->next = node;
// 		node->prev = list->rear;
// 		list->rear = node;
// 	}
// 	list->size++;
// }

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