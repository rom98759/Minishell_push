/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 21:11:09 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/02 21:11:09 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_ids(t_token *head)
{
	int		i;

	i = 0;
	while (head)
	{
		head->id = i;
		i++;
		head = head->next;
	}
}

int	add_cmd(t_token **new_line, t_token **cur, int *flag)
{
	t_token	*tmp;

	tmp = *cur;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == COMMAND && tmp->id != -1)
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
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_arg(t_token **new_line, t_token **cur, int *flag)
{
	t_token	*tmp;

	tmp = *cur;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARGUMENT && tmp->id != -1)
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
		}
		tmp = tmp->next;
	}
	return (0);
}

int	add_pipe(t_token **new_line, t_token **cur, int *flag)
{
	if (*cur && (*cur)->type == PIPE && (*cur)->id != -1)
	{
		if (*flag == 0)
		{
			*new_line = create_token(ft_strdup((*cur)->str), (*cur)->type);
			if (!*new_line)
				return (1);
			*flag = 1;
		}
		else
			add_token_to_list(new_line,
				create_token(ft_strdup((*cur)->str), (*cur)->type));
		(*cur)->id = -1;
		*cur = (*cur)->next;
	}
	return (0);
}
