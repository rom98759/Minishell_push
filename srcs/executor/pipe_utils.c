/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:32:55 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/25 10:36:29 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int status, int *newline_printed)
{
	if (WTERMSIG(status) == SIGINT && !(*newline_printed))
	{
		write(1, "\n", 1);
		*newline_printed = 1;
	}
	else if (WTERMSIG(status) == SIGQUIT)
		write(1, "Quit\n", 5);
}

/**
 * @brief Récupère le status de sortie des commandes
 *
 * @param cmd Structure de commande
 * @param last_pid PID du dernier processus
 * @return int Status de sortie
 */
void	get_exit_status(t_cmd *cmd, int last_pid)
{
	int		status;
	pid_t	wpid;
	int		newline_printed;

	newline_printed = 0;
	wpid = wait(&status);
	while (wpid > 0)
	{
		if (WIFSIGNALED(status))
			handle_signal(status, &newline_printed);
		if (wpid == last_pid)
		{
			if (WIFSIGNALED(status))
				cmd->exit_code = WTERMSIG(status) + 128;
			else if (WIFEXITED(status))
				cmd->exit_code = WEXITSTATUS(status);
		}
		wpid = wait(&status);
	}
}
