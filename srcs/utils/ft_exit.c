/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 10:15:09 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/06 16:00:34 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_exit_code(t_cmd *cmd, int status, char *msg)
{
	if (msg)
		ft_putendl_fd(msg, 2);
	cmd->exit_code = status;
}

/**
 * Exits the program with free and restore the terminal.
 * @param cmd The structure to free
 * @param exit_code The exit code
 */
void	ft_exit_free_cmd(t_cmd *cmd, int exit_code)
{
	ft_free_cmd(cmd, 1);
	exit(exit_code);
}
