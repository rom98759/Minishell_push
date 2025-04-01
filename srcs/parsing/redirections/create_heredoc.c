/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:02:54 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 10:13:23 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_heredoc	*create_heredoc_node(char *filename, char *delimiter)
{
	t_heredoc	*new_heredoc;

	new_heredoc = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!new_heredoc)
		return (NULL);
	new_heredoc->filename = ft_strdup(filename);
	free(filename);
	new_heredoc->delimiter = ft_strdup(delimiter);
	new_heredoc->next = NULL;
	if (!new_heredoc->filename || !new_heredoc->delimiter)
	{
		free(new_heredoc->filename);
		free(new_heredoc->delimiter);
		free(new_heredoc);
		return (NULL);
	}
	return (new_heredoc);
}

int	create_heredoc(t_cmd *cmd)
{
	t_token		*curr;
	t_heredoc	*new_heredoc;

	curr = cmd->token_list;
	if (!curr)
		return (-1);
	while (curr)
	{
		if (curr->type == HEREDOC)
		{
			new_heredoc = create_heredoc_node(generate_file(), curr->next->str);
			if (!new_heredoc)
			{
				ft_putendl_fd("minishell: malloc failed", 2);
				return (-1);
			}
			add_heredoc_to_list(&cmd->heredoc_list, new_heredoc);
		}
		curr = curr->next;
	}
	return (0);
}
