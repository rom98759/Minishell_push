/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:09:17 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/03 16:16:32 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validate the syntax of the tokens
 * @param tokens The list of tokens
 * @return 0 if the syntax is valid, 1 otherwise
 */
int	is_operator(t_token *token)
{
	return (token->type == PIPE || token->type == TRUNC || token->type == APPEND
		|| token->type == INPUT || token->type == HEREDOC);
}

/**
 * @brief Get the type of a token without considering redirections
 * @param input The user input
 * @param i The index of the token
 * @return The type of the token
 */
size_t	get_token_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == INPUT || tokens->type == TRUNC
			|| tokens->type == APPEND)
		{
			tokens = tokens->next->next;
			continue ;
		}
		count++;
		tokens = tokens->next;
	}
	return (count);
}

size_t	get_command_count(t_token *tokens)
{
	size_t	count;

	count = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*get_new_str_token(char *s, int type)
{
	char	*new_str;

	if (type == HEREDOC)
	{
		new_str = ft_strdup(s);
		if (!new_str)
			return (NULL);
		return (new_str);
	}
	new_str = remove_all_quote(s);
	if (!new_str)
		return (NULL);
	return (new_str);
}
