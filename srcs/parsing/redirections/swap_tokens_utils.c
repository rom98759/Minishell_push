/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tokens_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:42:25 by tdausque          #+#    #+#             */
/*   Updated: 2025/03/28 17:40:51 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_cmd(t_token **new_line, t_token **cur, int *flag, t_token **p)
{
	while (*cur && (*cur)->type != COMMAND)
		*cur = (*cur)->next;
	if (!*cur)
		return (1);
	if (*flag == 0)
	{
		*new_line = create_token((*cur)->str, COMMAND);
		*p = *new_line;
		*flag = 1;
	}
	else if (*flag == 1)
	{
		(*p)->next = create_token((*cur)->str, COMMAND);
		*p = (*p)->next;
	}
	return (0);
}

int	check_doc(t_token **cur, t_token **p, t_token *start)
{
	*cur = start;
	while (*cur)
	{
		if ((*cur)->type == HEREDOC)
		{
			(*p)->next = create_token("<<", HEREDOC);
			*p = (*p)->next;
			(*p)->next = create_token((*cur)->next->str, HEREDOC_FILE);
			*p = (*p)->next;
		}
		*cur = (*cur)->next;
	}
	return (0);
}

int	check_arg(t_token **cur, t_token *start, t_token **p)
{
	*cur = start;
	while (*cur && (*cur)->type != PIPE)
	{
		if ((*cur)->type == ARGUMENT)
		{
			(*p)->next = create_token((*cur)->str, ARGUMENT);
			(*p) = (*p)->next;
		}
		*cur = (*cur)->next;
	}
	if (!*cur)
		return (1);
	return (0);
}

int	check_trunc(t_token **cur, t_token *start, t_token **p)
{
	*cur = start;
	while (*cur)
	{
		if ((*cur)->type == TRUNC || (*cur)->type == APPEND
			|| (*cur)->type == INPUT)
		{
			(*p)->next = create_token((*cur)->str, (*cur)->type);
			*p = (*p)->next;
			(*p)->next = create_token((*cur)->next->str, FILENAME);
			*p = (*p)->next;
		}
		*cur = (*cur)->next;
	}
	return (0);
}

int	check_pipe(t_token **cur, t_token **p, t_token **start)
{
	if (!*cur)
		return (1);
	if ((*cur)->type == PIPE)
	{
		(*p)->next = create_token("|", PIPE);
		*p = (*p)->next;
	}
	*cur = (*cur)->next;
	*start = *cur;
	return (0);
}
