/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 17:23:07 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/17 11:04:10 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_error()
{

}

int main()
{
	t_command_list	list;
	char *line;

	signal_func();
	env_func();
	while(42)
	{
		line = readline("minishell>");
		if (!line)
			break;
		parsing(&list, line);
		execute_command();
		clear_data();
	}
	
	exit(0);
}