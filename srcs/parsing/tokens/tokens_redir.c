/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 19:31:46 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/21 19:31:46 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	detect_and_add_redirections_loop(t_token *t_current,
	t_redir **redir_list)
{
	t_redir	*new_redir;
	t_redir	*temp;

	new_redir = (t_redir *)malloc(sizeof(t_redir));
	if (!new_redir)
		return ;
	new_redir->type = t_current->type;
	new_redir->filename = ft_strdup(t_current->next->str);
	new_redir->fd = -1;
	new_redir->next = NULL;
	if (!*redir_list)
		*redir_list = new_redir;
	else
	{
		temp = *redir_list;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	detect_and_add_redirections(t_token *tokens, t_cmd *cmd)
{
	t_token	*t_current;
	t_redir	*redir_list;

	t_current = tokens;
	redir_list = NULL;
	while (t_current)
	{
		if ((t_current->type == TRUNC || t_current->type == APPEND
				|| t_current->type == INPUT) && t_current->next)
			detect_and_add_redirections_loop(t_current, &redir_list);
		t_current = t_current->next;
	}
	cmd->redir_list = redir_list;
}
