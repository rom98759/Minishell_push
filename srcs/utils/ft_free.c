/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:16:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 21:24:01 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Frees a tab of strings.
 * @param tab The tab to free.
 */
void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

/**
 * Frees a tab of strings.
 * @param tab The tab to free.
 */
void	ft_free_index_tab(char **tab, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_cmd2(t_cmd *cmd, int free_cmd)
{
	if (cmd->token_list)
	{
		ft_free_token_list(cmd->token_list);
		cmd->token_list = NULL;
	}
	if (cmd->redir_list)
	{
		ft_free_redir_list(cmd->redir_list);
		cmd->redir_list = NULL;
	}
	if (cmd->heredoc_list)
	{
		delete_heredoc(cmd->heredoc_list);
		cmd->heredoc_list = NULL;
		cmd->i_heredoc = 0;
	}
	if (free_cmd)
		free(cmd);
}

/**
 * Free and restore the terminal.
 * @param cmd The structure to free
 * @param free_cmd free the cmd structure ?
 */
void	ft_free_cmd(t_cmd *cmd, int free_cmd)
{
	if (cmd->env && free_cmd)
	{
		ft_free_tab(cmd->env);
		cmd->env = NULL;
	}
	if (cmd->stdcopy)
	{
		restore_std(cmd);
		free(cmd->stdcopy);
		cmd->stdcopy = NULL;
	}
	ft_free_cmd2(cmd, free_cmd);
}
