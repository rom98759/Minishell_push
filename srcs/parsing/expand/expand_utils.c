/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:32:00 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 20:21:48 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extract the name of the variable from a string
 * @param str The string to extract the variable name from
 * @param i The index of the string where the variable name starts
 */
char	*get_var_name(const char *str, size_t *i)
{
	size_t	start;

	start = *i;
	while (str[*i] && (str[*i] == '_' || ft_isalnum(str[*i])))
		(*i)++;
	return (ft_substr(str, start, *i - start));
}

/**
 * @brief Remove extra whitespace from a string.
 * @param str The string to be cleaned.
 * @return The cleaned string.
 */
char	*clean_whitespace(const char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!result)
		return (NULL);
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		while (str[i] && !is_whitespace(str[i]))
			result[j++] = str[i++];
		if (str[i] && j > 0)
			result[j++] = ' ';
	}
	if (j > 0 && result[j - 1] == ' ')
		j--;
	result[j] = '\0';
	return (result);
}

/**
 * @brief Retrieve and clean the value of an environment variable.
 * @param var_name The name of the variable.
 * @param exp_data The expansion data.
 * @return The cleaned variable value.
 */
char	*parse_var_value(char *var_name, t_expand *exp_data)
{
	char	*value;
	char	*cleaned_value;

	value = my_getenv(var_name, exp_data->env_data->env);
	if (!value || *value == '\0')
		return (ft_strdup(""));
	if (exp_data->quote == 0)
		cleaned_value = clean_whitespace(value);
	else
		cleaned_value = ft_strdup(value);
	return (cleaned_value);
}

/**
 * @brief Handle the quotes
 * @param c The current character
 * @param quote The current quote status
 * @return The new quote status (0: no quote, 1: simple quote, 2: double quote)
 */
int	handle_quotes(char c, int quote)
{
	if (c == '"' && quote == 0)
		return (2);
	else if (c == '"' && quote == 2)
		return (0);
	else if (c == '\'' && quote == 0)
		return (1);
	else if (c == '\'' && quote == 1)
		return (0);
	return (quote);
}
