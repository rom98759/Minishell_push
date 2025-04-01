/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_tokens.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 08:56:42 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/29 19:39:59 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handle the pipe syntax
 * @param current The current token
 * @param tokens The list of tokens
 * @return 0 if the syntax is valid, 1 otherwise
 */
int	handle_pipe_syntax(t_token *current, t_token *tokens, t_cmd *cmd)
{
	if (!current->next || current == tokens)
		return (handle_error("Syntax error: invalid pipe position",
				258, cmd));
	if (current->next->type == PIPE)
		return (handle_error("Syntax error: consecutive pipes are invalid",
				258, cmd));
	return (0);
}

/**
 * @brief Handle the redirection syntax
 * @param current The current token
 * @return 0 if the syntax is valid, 1 otherwise
 */
int	handle_redirection_syntax(t_token *current, t_cmd *cmd)
{
	if (current->type == HEREDOC)
		cmd->i_heredoc++;
	if (!current->next)
		return (handle_error("Syntax error: redirection without a target",
				258, cmd));
	if (current->next->type != FILENAME && current->next->type != ARGUMENT
		&& current->next->type != HEREDOC_FILE)
		return (handle_error("Syntax error: invalid redirection target",
				258, cmd));
	if (current->next->type == TRUNC || current->next->type == APPEND
		|| current->next->type == INPUT || current->next->type == HEREDOC)
		return (handle_error("Syntax error: consecutive redirections invalid",
				258, cmd));
	if (cmd->i_heredoc > 16)
		return (handle_error("maximum here-document count exceeded",
				2, cmd));
	return (0);
}

/**
 * @brief Handle the filename syntax
 * @param current The current token
 * @param tokens The list of tokens
 * @return 0 if the syntax is valid, 1 otherwise
 */
int	handle_filename_syntax(t_token *current, t_token *tokens, t_cmd *cmd)
{
	if (current == tokens || (current->next && current->next->type == FILENAME))
		return (handle_error("Syntax error: invalid filename position",
				258, cmd));
	return (0);
}

/**
 * @brief Validate the syntax of the tokens
 * @param tokens The list of tokens
 * @return 0 if the syntax is valid, 1 otherwise
 */
int	validate_syntax(t_token *tokens, t_cmd *cmd)
{
	t_token	*current;
	int		result;

	current = tokens;
	while (current)
	{
		if (!is_valid_token_type(current->type))
			return (handle_error("Syntax error: unknown operator",
					258, cmd));
		if (current->type == PIPE)
			result = handle_pipe_syntax(current, tokens, cmd);
		else if (current->type == TRUNC || current->type == APPEND
			|| current->type == INPUT || current->type == HEREDOC)
			result = handle_redirection_syntax(current, cmd);
		else if (current->type == FILENAME)
			result = handle_filename_syntax(current, tokens, cmd);
		else
			result = 0;
		if (result != 0)
			return (result);
		current = current->next;
	}
	return (0);
}
