/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 20:17:40 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/29 19:32:08 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Tokenize the user input
 * @param input The user input
 * @return The list of tokens
 */
static t_token	*create_and_add_token(char *input, int type, t_token *tokens)
{
	t_token	*new_token;
	char	*tmp;
	char	*str;

	tmp = get_new_str_token(input, type);
	if (!tmp)
	{
		ft_free_token_list(tokens);
		return (NULL);
	}
	str = ft_strdup(tmp);
	free(tmp);
	if (!str)
	{
		ft_free_token_list(tokens);
		return (NULL);
	}
	new_token = create_token(str, type);
	if (!new_token)
	{
		ft_free_token_list(tokens);
		return (NULL);
	}
	add_token_to_list(&tokens, new_token);
	return (tokens);
}

static t_token	*tokenize_loop(char **input, t_token *tokens)
{
	int		i;
	int		type;

	i = 0;
	while (input[i])
	{
		type = get_token_type(input, i);
		tokens = create_and_add_token(input[i], type, tokens);
		if (!tokens)
			return (NULL);
		i++;
	}
	return (tokens);
}

t_token	*tokenize(char **input)
{
	t_token	*tokens;

	if (!input || !*input)
		return (create_token(ft_strdup(""), UNKNOWN_OPERATOR));
	tokens = NULL;
	return (tokenize_loop(input, tokens));
}

/**
 * @brief Tokenize and validate the user input
 * @param input The user input
 * @return The list of tokens if the syntax is valid, NULL otherwise
 */
static int	tokenize_and_validate_impl(t_token **tokens, t_cmd *cmd)
{
	if (!*tokens)
		return (-1);
	if ((*tokens)->type == UNKNOWN_OPERATOR)
	{
		ft_free_token_list(*tokens);
		return (-1);
	}
	detect_filenames(*tokens);
	detect_commands_and_arguments(*tokens);
	detect_and_add_redirections(*tokens, cmd);
	if (validate_syntax(*tokens, cmd) != 0)
	{
		ft_free_token_list(*tokens);
		return (-1);
	}
	cmd->token_list = *tokens;
	if (!cmd->token_list)
		ft_free_token_list(*tokens);
	return (0);
}

int	tokenize_and_validate(char **input, t_cmd *cmd)
{
	char	**new;
	t_token	*tokens;

	new = expand_var(input, cmd->env, cmd->exit_code);
	ft_free_tab(input);
	tokens = tokenize(new);
	ft_free_tab(new);
	if (tokenize_and_validate_impl(&tokens, cmd) == -1)
		return (-1);
	return (0);
}
