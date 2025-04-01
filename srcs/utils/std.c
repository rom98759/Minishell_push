/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:50:35 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/06 17:20:41 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_std(t_cmd *cmd)
{
	cmd->stdcopy = malloc(sizeof(t_stdcopy));
	if (!cmd->stdcopy)
		return (-1);
	cmd->stdcopy->stdin_copy = dup(STDIN_FILENO);
	cmd->stdcopy->stdout_copy = dup(STDOUT_FILENO);
	cmd->stdcopy->stderr_copy = dup(STDERR_FILENO);
	if (cmd->stdcopy->stdin_copy == -1
		|| cmd->stdcopy->stdout_copy == -1
		|| cmd->stdcopy->stderr_copy == -1)
	{
		free(cmd->stdcopy);
		cmd->stdcopy = NULL;
		return (-1);
	}
	return (0);
}

void	close_std(t_cmd *cmd)
{
	if (cmd->stdcopy)
	{
		close(cmd->stdcopy->stdin_copy);
		close(cmd->stdcopy->stdout_copy);
		close(cmd->stdcopy->stderr_copy);
		free(cmd->stdcopy);
		cmd->stdcopy = NULL;
	}
}

int	restore_std(t_cmd *cmd)
{
	if (cmd->stdcopy)
	{
		if (dup2(cmd->stdcopy->stdin_copy, STDIN_FILENO) == -1
			|| dup2(cmd->stdcopy->stdout_copy, STDOUT_FILENO) == -1
			|| dup2(cmd->stdcopy->stderr_copy, STDERR_FILENO) == -1)
		{
			close_std(cmd);
			return (-1);
		}
		close_std(cmd);
	}
	return (0);
}
