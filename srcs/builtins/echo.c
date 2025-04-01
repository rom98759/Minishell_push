/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:33:39 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/31 17:33:39 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour traiter l'option -n
static int	parse_n_option(t_token **token)
{
	int	n_option;
	int	i;

	n_option = 0;
	while (*token && (*token)->str[0] == '-' && (*token)->str[1] == 'n')
	{
		i = 1;
		while ((*token)->str[i] && (*token)->str[i] == 'n')
			i++;
		if ((*token)->str[i] != '\0')
			break ;
		n_option = 1;
		*token = (*token)->next;
	}
	return (n_option);
}

// Fonction pour afficher les arguments séparés par un espace
static void	print_args_table(char **args)
{
	int	j;

	j = 0;
	while (args && args[j])
	{
		ft_putstr_fd(args[j], 1);
		if (args[j + 1])
			ft_putchar_fd(' ', 1);
		j++;
	}
}

/**
 * La commande builtin echo
 * Gestion de l'option -n
 * @param token liste de tokens
 * @return 0 si la commande a réussi, 1 sinon
 */
int	ft_echo(t_token *token)
{
	int		n_option;
	char	**args;

	n_option = parse_n_option(&token);
	args = token_to_tab_sin_redir(token);
	print_args_table(args);
	if (args)
		ft_free_tab(args);
	if (!n_option)
		ft_putchar_fd('\n', 1);
	return (0);
}
