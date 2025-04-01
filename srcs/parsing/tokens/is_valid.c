/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 18:45:24 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/29 18:45:24 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if the token type is valid
 * @param type The type to check
 * @return 1 if the type is valid, 0 otherwise
 */
int	is_valid_token_type(int type)
{
	return (type == TRUNC || type == APPEND || type == INPUT
		|| type == HEREDOC || type == PIPE || type == COMMAND
		|| type == ARGUMENT || type == FILENAME || type == HEREDOC_FILE);
}

/**
 * @brief Check if the filename is valid
 * @param str The filename to check
 * @return 1 if the filename is valid, 0 otherwise
 */
int	is_valid_filename(char *str)
{
	if (!str || *str == '\0' || ft_strchr(str, '|') || ft_strchr(str, '&')
		|| ft_strchr(str, ';') || ft_strchr(str, '$'))
		return (0);
	return (1);
}

/**
 * @brief Check if the command is valid
 * @param str The command to check
 * @return 1 if the command is valid, 0 otherwise
 */
int	is_valid_command(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (access(str, X_OK) == 0)
		return (1);
	if (is_builtin(str) != 0)
		return (1);
	return (0);
}
