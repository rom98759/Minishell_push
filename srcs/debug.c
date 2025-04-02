/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:47:31 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/03 16:48:40 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_type(int type)
{
	if (type == TRUNC)
		return ("TRUNC");
	if (type == APPEND)
		return ("APPEND");
	if (type == INPUT)
		return ("INPUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == PIPE)
		return ("PIPE");
	if (type == COMMAND)
		return ("COMMAND");
	if (type == ARGUMENT)
		return ("ARGUMENT");
	if (type == FILENAME)
		return ("FILENAME");
	if (type == HEREDOC_FILE)
		return ("HEREDOC_FILE");
	return ("UNKNOWN");
}

char	*get_color(int type)
{
	if (type == TRUNC)
		return ("\033[0;31m");
	if (type == APPEND)
		return ("\033[0;32m");
	if (type == INPUT)
		return ("\033[0;33m");
	if (type == HEREDOC)
		return ("\033[0;34m");
	if (type == PIPE)
		return ("\033[0;35m");
	if (type == COMMAND)
		return ("\033[0;36m");
	if (type == ARGUMENT)
		return ("\033[0;37m");
	if (type == FILENAME)
		return ("\033[1;33m");
	if (type == HEREDOC_FILE)
		return ("\033[1;34m");
	return ("\033[0m");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		printf("%sToken: %s (type: %s)\033[0m\n",
			get_color(current->type),
			current->str,
			get_type(current->type));
		current = current->next;
	}
	while (i < 50)
	{
		printf("-");
		i++;
	}
	printf("\n");
}
