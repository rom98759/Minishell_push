/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:31:03 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 11:13:56 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	add_token_to_command(t_token **command, char *str, int type)
{
	char	*dup;
	t_token	*new;

	dup = ft_strdup(str);
	if (!dup)
	{
		ft_free_token_list(*command);
		return (0);
	}
	new = create_token(dup, type);
	if (!new || !new->str)
	{
		free(dup);
		ft_free_token_list(*command);
		return (0);
	}
	add_token_to_list(command, new);
	return (1);
}

t_token	*get_command(t_token *tokens, int indice)
{
	t_token	*command;
	t_token	*current;
	int		current_index;

	command = NULL;
	current = tokens;
	current_index = 0;
	while (current && current_index <= indice)
	{
		if (current->type == PIPE)
		{
			current_index++;
			current = current->next;
			continue ;
		}
		if (current_index == indice)
		{
			if (!add_token_to_command(&command, current->str, current->type))
				return (NULL);
		}
		current = current->next;
	}
	return (command);
}

char	*get_name_command(t_token *tokens, int indice)
{
	t_token	*current;
	t_token	*tmp;
	char	*command_name;

	current = get_command(tokens, indice);
	if (!current)
		return (NULL);
	tmp = current;
	while (current && current->type != COMMAND)
		current = current->next;
	if (current)
		command_name = ft_strdup(current->str);
	else
		command_name = NULL;
	ft_free_token_list(tmp);
	return (command_name);
}
