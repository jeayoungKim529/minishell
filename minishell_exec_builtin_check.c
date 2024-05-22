/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec_builtin_check.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeakim <jeakim@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 15:33:35 by jeakim            #+#    #+#             */
/*   Updated: 2024/05/22 13:25:11 by jeakim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_builtin_command(char **com)
{
	if (strncmp("cd", com[0], 3) == 0)
		return (1);
	else if (strncmp("pwd", com[0], 4) == 0)
		return (1);
	else if (strncmp("echo", com[0], 5) == 0)
		return (1);
	else if (strncmp("env", com[0], 4) == 0)
		return (1);
	else if (strncmp("export", com[0], 7) == 0)
		return (1);
	else if (strncmp("unset", com[0], 6) == 0)
		return (1);
	else if (strncmp("exit", com[0], 5) == 0)
		return (1);
	return (0);
}