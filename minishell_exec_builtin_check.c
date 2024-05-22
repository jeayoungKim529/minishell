/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_check.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/17 16:14:08 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_option()
{

}

int	check_option_n()
{

}

int	check_path()
{

}
int	check_arg()
{

}

int	check_builtin_command(char **com)
{
	if (strncmp("cd", com[0], 3) == 0)
		return (check_path());
	else if (strncmp("pwd", com[0], 4) == 0)
		return (check_option());
	else if (strncmp("echo", com[0], 5) == 0)
		return (check_option_n());
	else if (strncmp("env", com[0], 4) == 0)
		return (check_arg() && check_option());
	else if (strncmp("export", com[0], 7) == 0)
		return (check_option());
	else if (strncmp("unset", com[0], 6) == 0)
		return (check_option());
	else if (strncmp("exit", com[0], 5) == 0)
		return (check_option());
	return (0);
}