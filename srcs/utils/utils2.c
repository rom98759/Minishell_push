/* ************************************************************************** */
/*		                                                                    */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:41:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 10:49:46 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Remove quotes from a string (at the beginning and end)
 * @param str The string to clean
 * @return The cleaned string
 */
char	*remove_quotes(char *str)
{
	int		start;
	int		end;
	char	*new_str;
	int		i;

	start = 0;
	end = ft_strlen(str) - 1;
	if ((str[start] == '"' || str[start] == '\'')
		&& (str[end] == '"' || str[end] == '\'') && start != end)
	{
		start++;
		end--;
	}
	new_str = malloc(end - start + 2);
	if (!new_str)
		return (NULL);
	i = 0;
	while (start <= end)
	{
		new_str[i] = str[start];
		i++;
		start++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static int	count_new_len(char *str)
{
	int		i;
	int		new_len;
	char	quote;

	i = 0;
	new_len = 0;
	quote = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '"') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = 0;
		else if ((str[i] == '\'' || str[i] == '"')
			&& str[i + 1] == str[i] && !quote)
			i += 2;
		else
			new_len++;
		i++;
	}
	return (new_len);
}

char	*remove_all_quote(char *s)
{
	int		i;
	int		j;
	char	*new_str;
	char	q;

	if (!s)
		return (NULL);
	new_str = (char *)ft_calloc(count_new_len(s) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	i = -1;
	j = 0;
	q = 0;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '"') && !q)
			q = s[i];
		else if (s[i] == q)
			q = 0;
		else if ((s[i] == '\'' || s[i] == '"') && s[i + 1] == s[i] && !q)
			i += 2;
		else
			new_str[j++] = s[i];
	}
	return (new_str);
}
