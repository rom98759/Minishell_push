/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:10:39 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/02 18:10:39 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_file(t_token **new_line, t_token **tmp)
{
	t_token	*file;

	if ((*tmp)->type == FILENAME || (*tmp)->type == HEREDOC_FILE)
	{
		file = create_token(ft_strdup((*tmp)->str), (*tmp)->type);
		if (!file)
			return (1);
		add_token_to_list(new_line, file);
		(*tmp)->id = -1;
	}
	return (0);
}

static int	add_redir_in(t_token **new_line, t_token **cur, int *flag)
{
	t_token	*tmp;

	tmp = *cur;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == INPUT || tmp->type == HEREDOC) && tmp->id != -1)
		{
			if (*flag == 0)
			{
				*new_line = create_token(ft_strdup(tmp->str), tmp->type);
				if (!*new_line)
					return (1);
				*flag = 1;
			}
			else
				add_token_to_list(new_line,
					create_token(ft_strdup(tmp->str), tmp->type));
			tmp->id = -1;
			if (add_file(new_line, &tmp->next) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static int	add_redi_out(t_token **new_line, t_token **cur, int *flag)
{
	t_token	*tmp;

	tmp = *cur;
	while (tmp && tmp->type != PIPE)
	{
		if ((tmp->type == TRUNC || tmp->type == APPEND) && tmp->id != -1)
		{
			if (*flag == 0)
			{
				*new_line = create_token(ft_strdup(tmp->str), tmp->type);
				if (!*new_line)
					return (1);
				*flag = 1;
			}
			else
				add_token_to_list(new_line,
					create_token(ft_strdup(tmp->str), tmp->type));
			tmp->id = -1;
			if (add_file(new_line, &tmp->next) == 1)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

/* Fonction swap_token modifiée */
t_token	*swap_token(t_cmd *cmd)
{
	t_token	*cur;
	t_token	*new_line;
	int		flag;

	cur = cmd->token_list;
	flag = 0;
	new_line = NULL;
	while (cur)
	{
		if (add_cmd(&new_line, &cur, &flag) == 1)
			return (NULL);
		if (add_arg(&new_line, &cur, &flag) == 1)
			return (NULL);
		if (add_redir_in(&new_line, &cur, &flag) == 1)
			return (NULL);
		if (add_redi_out(&new_line, &cur, &flag) == 1)
			return (NULL);
		while (cur && cur->id == -1)
			cur = cur->next;
		if (add_pipe(&new_line, &cur, &flag) == 1)
			return (NULL);
	}
	update_ids(new_line);
	return (new_line);
}
