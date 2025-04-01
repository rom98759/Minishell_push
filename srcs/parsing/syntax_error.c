/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdausque <tdausque@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:39:04 by tdausque          #+#    #+#             */
/*   Updated: 2025/01/23 18:44:01 by tdausque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Vérifie si une chaîne de caractères contient des guillemets
 * non fermés
 *
 * @param str Chaîne de caractères
 * @return int 1 si les guillemets sont fermés, 0 sinon
 */
int	quotes_error(char *str)
{
	int	i;
	int	inside_single_quote;
	int	inside_double_quote;

	if (!str)
		return (0);
	i = 0;
	inside_single_quote = 0;
	inside_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !inside_double_quote)
			inside_single_quote = !inside_single_quote;
		else if (str[i] == '\"' && !inside_single_quote)
			inside_double_quote = !inside_double_quote;
		i++;
	}
	if (!inside_single_quote && !inside_double_quote)
		return (1);
	return (0);
}

/**
 * @brief Vérifie si la syntaxe est correcte
 *
 * @param tab Tableau de chaînes de caractères
 * @param cmd Structure de commande
 * @return int 1 si la syntaxe est correcte, 0 sinon
 */
int	syntax_error(char **tab, t_cmd *cmd)
{
	int	i;

	if (!tab)
		return (0);
	i = 0;
	while (tab[i])
	{
		if (!quotes_error(tab[i]))
		{
			ft_update_exit_code(cmd, 2, "Syntax error: unclosed quote");
			return (0);
		}
		i++;
	}
	return (1);
}
