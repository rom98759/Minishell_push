/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:51:03 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 10:23:41 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Helper function to convert a HEREDOC token into an INPUT token.
	Renvoie 1 en cas de succès, 0 en cas d'erreur. */
static int	convert_heredoc_to_input(t_token **token, t_token *first)
{
	(*token)->type = INPUT;
	free((*token)->str);
	(*token)->str = ft_strdup("<");
	if (!(*token)->str)
	{
		ft_free_token_list(first);
		ft_putstr_fd("minishell: erreur d'allocation mémoire\n", 2);
		return (0);
	}
	*token = (*token)->next;
	return (1);
}

/* Helper function to traiter le token HEREDOC_FILE associé.
	  Renvoie 1 en cas de succès, 0 en cas d'erreur. */
static int	process_heredoc_file(t_cmd *cmd, t_token **token, t_token *first)
{
	t_heredoc	*heredoc;

	if (*token && (*token)->type == HEREDOC_FILE)
	{
		heredoc = get_heredoc(cmd->heredoc_list, cmd->i_heredoc);
		if (!heredoc)
		{
			ft_free_token_list(first);
			ft_putstr_fd("minishell: erreur de récupération du heredoc\n", 2);
			return (0);
		}
		free((*token)->str);
		(*token)->str = ft_strdup(heredoc->filename);
		(*token)->type = FILENAME;
		cmd->i_heredoc++;
	}
	return (1);
}

void	change_heredoc_to_input(t_cmd *cmd)
{
	t_token		*current;
	t_token		*first;

	current = cmd->token_list;
	first = current;
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (!convert_heredoc_to_input(&current, first)
				|| !process_heredoc_file(cmd, &current, first))
			{
				return ;
			}
		}
		else
			current = current->next;
	}
	cmd->token_list = first;
}
