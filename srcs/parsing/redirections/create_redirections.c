/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:14:18 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 11:14:18 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_redir_to_list(t_redir **head, t_redir *new_redir)
{
	t_redir	*tmp;

	if (!new_redir)
		return ;
	if (!*head)
	{
		*head = new_redir;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_redir;
}

static t_redir	*create_redirection(char *filename, int type)
{
	t_redir	*new_redir;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = type;
	new_redir->filename = ft_strdup(filename);
	new_redir->fd = -1;
	new_redir->next = NULL;
	return (new_redir);
}

// Create a list of t_redir from the tokens index list
void	add_redirections(t_cmd *cmd, t_token *current)
{
	t_redir	*new_redir;

	while (current)
	{
		if (current->next && (current->type == TRUNC || current->type == APPEND
				|| current->type == INPUT || current->type == HEREDOC))
		{
			new_redir = create_redirection(current->next->str, current->type);
			if (!new_redir)
			{
				ft_free_token_list(current);
				ft_free_cmd(cmd, 1);
				ft_putendl_fd("minishell: malloc failed", 2);
				exit(1);
			}
			add_redir_to_list(&cmd->redir_list, new_redir);
		}
		current = current->next;
	}
}

void	create_redir(t_cmd *cmd, int index)
{
	t_token	*current;
	t_token	*tmp;

	if (cmd->redir_list)
	{
		ft_free_redir_list(cmd->redir_list);
		cmd->redir_list = NULL;
	}
	current = get_command(cmd->token_list, index);
	if (!current)
		return ;
	tmp = current;
	add_redirections(cmd, current);
	ft_free_token_list(tmp);
}
