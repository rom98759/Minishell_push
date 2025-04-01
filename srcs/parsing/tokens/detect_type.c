/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:34:12 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 09:34:36 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new token
 * @param str The string to store in the token
 * @param type The type of the token
 * @return The type of the token (redirection)
 */
int	detect_redirections(char *str)
{
	if (ft_strcmp(str, ">") == 0)
	{
		if (ft_strcmp(str, ">>") == 0)
			return (APPEND);
		return (TRUNC);
	}
	if (ft_strcmp(str, "<") == 0)
	{
		if (ft_strcmp(str, "<<") == 0)
			return (HEREDOC);
		return (INPUT);
	}
	return (-1);
}

/**
 * @brief Get the type of a token (redirection, pipe or argument)
 * @param str The string to check
 * @return The type of the token, or ARGUMENT by default
 */
int	get_token_type(char **input, int i)
{
	if (ft_strlen(input[i]) == 0)
		return (ARGUMENT);
	if (ft_strcmp(input[i], "|") == 0)
		return (PIPE);
	if (ft_strcmp(input[i], ">") == 0)
		return (TRUNC);
	if (ft_strcmp(input[i], ">>") == 0)
		return (APPEND);
	if (ft_strcmp(input[i], "<") == 0)
		return (INPUT);
	if (ft_strcmp(input[i], "<<") == 0)
		return (HEREDOC);
	if (i > 0 && detect_redirections(input[i - 1]) != -1)
	{
		if (is_valid_filename(input[i]))
			return (FILENAME);
	}
	if (i == 0 || ft_strcmp(input[i - 1], "|") == 0)
	{
		if (is_valid_command(input[i]))
			return (COMMAND);
	}
	return (ARGUMENT);
}

/**
 * @brief Detect if a token is a command or an argument
 * @param str The string to store in the token
 * @param type The type of the token
 * @return The type of the token (command or argument)
 */
void	detect_commands_and_arguments(t_token *tokens)
{
	t_token	*current;
	int		is_command;

	current = tokens;
	is_command = 1;
	while (current)
	{
		if (current->type == COMMAND && is_command)
		{
			is_command = 0;
		}
		else if (current->type == ARGUMENT && is_command)
		{
			current->type = COMMAND;
			is_command = 0;
		}
		else if (current->type == PIPE)
		{
			is_command = 1;
		}
		current = current->next;
	}
}

/**
 * @brief Detect filenames for redirections
 * @param tokens The list of tokens
 */
void	detect_filenames(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT)
		{
			if (current->next && (current->next->type == ARGUMENT
					|| current->next->type == COMMAND))
				current->next->type = FILENAME;
		}
		else if (current->type == HEREDOC)
		{
			if (current->next && (current->next->type == FILENAME
					|| current->next->type == ARGUMENT))
				current->next->type = HEREDOC_FILE;
		}
		current = current->next;
	}
}
