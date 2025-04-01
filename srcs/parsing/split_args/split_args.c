/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 11:35:17 by tdausque          #+#    #+#             */
/*   Updated: 2025/03/31 17:19:53 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	advance_token(char *cmd, int *i)
{
	if (cmd[*i] == '\'' || cmd[*i] == '"')
		handle_quote(cmd, i, cmd[*i]);
	else if (is_op_split(cmd + *i))
		*i += is_op_split(cmd + *i);
	else
	{
		while (cmd[*i] && !is_whitespace(cmd[*i]) && !is_op_split(cmd + *i))
		{
			if (cmd[*i] == '\'' || cmd[*i] == '"')
				handle_quote(cmd, i, cmd[*i]);
			else
				(*i)++;
		}
	}
}

static int	count_words(char *cmd)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (cmd[i])
	{
		skip_whitespace(cmd, &i);
		if (!cmd[i])
			break ;
		count++;
		advance_token(cmd, &i);
	}
	return (count);
}

static void	process_token(char *cmd, int *i, char **tab, int *j)
{
	int		start;

	start = *i;
	if (cmd[*i] == '\'' || cmd[*i] == '"')
		handle_quote(cmd, i, cmd[*i]);
	else if (is_op_split(cmd + *i))
		*i += is_op_split(cmd + *i);
	else
	{
		while (cmd[*i] && !is_whitespace(cmd[*i]) && !is_op_split(cmd + *i))
		{
			if (cmd[*i] == '\'' || cmd[*i] == '"')
				handle_quote(cmd, i, cmd[*i]);
			else
				(*i)++;
		}
	}
	tab[(*j)++] = dup_word(cmd, start, *i);
}

char	**ft_subcmd(char *cmd)
{
	int		i;
	int		j;
	char	**tab;

	tab = (char **)malloc(sizeof(char *) * (count_words(cmd) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	while (cmd[i])
	{
		skip_whitespace(cmd, &i);
		if (!cmd[i])
			break ;
		process_token(cmd, &i, tab, &j);
	}
	tab[j] = NULL;
	free(cmd);
	return (tab);
}
