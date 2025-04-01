/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:37:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/25 13:06:11 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_op_split(char *s)
{
	if (!s)
		return (0);
	if (*s == '>')
	{
		if (*(s + 1) == '>')
			return (2);
		return (1);
	}
	if (*s == '<')
	{
		if (*(s + 1) == '<')
			return (2);
		return (1);
	}
	if (*s == '|')
		return (1);
	return (0);
}

void	skip_whitespace(char *cmd, int *i)
{
	while (cmd[*i] && is_whitespace(cmd[*i]))
		(*i)++;
}

void	handle_quote(char *cmd, int *i, char quote)
{
	(*i)++;
	while (cmd[*i] && cmd[*i] != quote)
		(*i)++;
	if (cmd[*i] == quote)
		(*i)++;
	while (cmd[*i] && !is_whitespace(cmd[*i]) && !is_op_split(cmd + *i))
	{
		if (cmd[*i] == '\'' || cmd[*i] == '"')
			handle_quote(cmd, i, cmd[*i]);
		else
			(*i)++;
	}
}

char	*dup_word(char *str, int start, int end)
{
	char	*dup;
	int		len;
	int		i;

	len = end - start;
	if (len == 0)
		return (ft_strdup(""));
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (start < end)
		dup[i++] = str[start++];
	dup[i] = '\0';
	return (dup);
}
