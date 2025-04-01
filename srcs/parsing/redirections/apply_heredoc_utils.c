/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 21:01:10 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 21:01:10 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_eof_heredoc(char *line, t_heredoc *heredoc)
{
	char	*new;

	new = remove_all_quote(heredoc->delimiter);
	if (!new)
		return (1);
	if (ft_strcmp(line, new) == 0)
	{
		free(new);
		return (1);
	}
	free(new);
	return (0);
}
