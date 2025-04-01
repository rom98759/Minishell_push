/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:16:44 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/06 16:54:48 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Exits the program with an error message.
 * @param msg The error message to display.
 */
void	ft_exit_error(char *msg, int exit_code)
{
	if (msg)
		printf("%s\n", msg);
	exit(exit_code);
}

/**
 * Gestion des erreurs avec un code de retour.
 * @param message Le message d'erreur à afficher.
 * @param exit_code Le code de sortie spécifique (si != 0).
 * @param cmd La structure de commande.
 * @return -1
 */
int	handle_error(char *message, int exit_code, t_cmd *cmd)
{
	if (message)
	{
		ft_putendl_fd(message, 2);
	}
	else
		ft_putendl_fd("minishell: error\n", 2);
	cmd->exit_code = (exit_code % 256);
	return (-1);
}
