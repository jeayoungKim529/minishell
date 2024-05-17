/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_builtin_check.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:35:19 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/16 19:43:48 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exec.h"

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

int	check_builtin_comment(t_info *info)
{
	if (strncmp("cd", , 3) == 0)
		return (check_path());
	else if (strncmp("pwd", , 4) == 0)
		return (check_option());
	else if (strncmp("echo", , 5) == 0)
		return (check_option_n());
	else if (strncmp("env", , 4) == 0)
		return (check_arg() && check_option());
	else if (strncmp("export", , 7) == 0)
		return (check_option());
	else if (strncmp("unset", , 6) == 0)
		return (check_option());
	else if (strncmp("exit", , 5) == 0)
		return (check_option());
	return (0);
}
