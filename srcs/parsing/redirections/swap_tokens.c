/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdausque <tdausque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:44:36 by tdausque          #+#    #+#             */
/*   Updated: 2025/03/28 14:43:19 by tdausque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*swap_token(t_cmd *cmd)
{
	t_token	*cur;
	t_token	*new_line;
	t_token	*p;
	t_token	*start;
	int		flag;

	cur = cmd->token_list;
	start = cmd->token_list;
	flag = 0;
	new_line = NULL;
	while (cur)
	{
		while (cur && cur->type != PIPE)
		{
			if (check_cmd(&new_line, &cur, &flag, &p))
				return (NULL);
			check_doc(&cur, &p, start);
			check_trunc(&cur, start, &p);
			check_arg(&cur, start, &p);
		}
		if (!cur)
			break ;
		check_pipe(&cur, &p, &start);
	}
	return (new_line);
}
