/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 18:04:36 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 08:57:02 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->str = str;
	token->type = type;
	token->id = 0;
	token->next = NULL;
	return (token);
}

void	add_token_to_list(t_token **head, t_token *new_token)
{
	t_token	*current;

	if (!*head)
	{
		new_token->id = 0;
		*head = new_token;
	}
	else
	{
		current = *head;
		while (current->next)
			current = current->next;
		new_token->id = current->id + 1;
		current->next = new_token;
	}
}

void	ft_free_token_list(t_token *head)
{
	t_token	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

static int	fill_tab_without_redirects(char **tab, t_token *tokens)
{
	size_t	i;
	t_token	*temp;

	i = 0;
	temp = tokens;
	while (temp)
	{
		if (temp->type == INPUT || temp->type == TRUNC || temp->type == APPEND)
		{
			temp = temp->next->next;
			continue ;
		}
		tab[i] = ft_strdup(temp->str);
		if (!tab[i])
		{
			ft_free_index_tab(tab, i);
			return (-1);
		}
		temp = temp->next;
		i++;
	}
	tab[i] = NULL;
	return (0);
}

char	**token_to_tab_sin_redir(t_token *tokens)
{
	size_t	len;
	char	**tab;

	len = get_token_count(tokens);
	tab = (char **)ft_calloc(len + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	if (fill_tab_without_redirects(tab, tokens) == -1)
		return (NULL);
	return (tab);
}
