/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:16:02 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 11:12:40 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Crée un heredoc
 * @param cmd Structure de commande
 * @param index Index de la commande
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int	handle_heredocs(t_cmd *cmd)
{
	signal(SIGINT, handle_heredoc_sigint);
	if (cmd->heredoc_list)
	{
		delete_heredoc(cmd->heredoc_list);
		cmd->heredoc_list = NULL;
	}
	if (create_heredoc(cmd) == -1)
		return (-1);
	if (apply_heredoc(cmd) == -1)
	{
		delete_heredoc(cmd->heredoc_list);
		cmd->heredoc_list = NULL;
		return (-1);
	}
	signal(SIGINT, handle_sigint);
	change_heredoc_to_input(cmd);
	return (0);
}
