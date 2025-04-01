/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:27:59 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/31 17:27:59 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Check if a command is a builtin
 * @param str The command to check
 * @return 0 if not a builtin, 1 if echo, 2 if cd, 3 if pwd,
 * 4 if export, 5 if unset, 6 if env, 7 if exit
 */
int	is_builtin(char *str)
{
	char	*cleaned_str;
	int		valid;

	cleaned_str = remove_quotes(str);
	if (cleaned_str == NULL)
		return (0);
	valid = 0;
	if (ft_strcmp(cleaned_str, "echo") == 0)
		valid = 1;
	else if (ft_strcmp(cleaned_str, "cd") == 0)
		valid = 2;
	else if (ft_strcmp(cleaned_str, "pwd") == 0)
		valid = 3;
	else if (ft_strcmp(cleaned_str, "export") == 0)
		valid = 4;
	else if (ft_strcmp(cleaned_str, "unset") == 0)
		valid = 5;
	else if (ft_strcmp(cleaned_str, "env") == 0)
		valid = 6;
	else if (ft_strcmp(cleaned_str, "exit") == 0)
		valid = 7;
	free(cleaned_str);
	return (valid);
}
