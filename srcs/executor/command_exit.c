/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:49:31 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/21 11:05:25 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gère les erreurs de commandes
 *
 * @param path Chemin de la commande
 * @return int Code de retour de la commande
 */
int	command_exit(char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	if (is_directory(path) && ft_strchr(path, '/'))
	{
		ft_putendl_fd(": Is a directory", 2);
		return (126);
	}
	else if (ft_strchr(path, '/'))
	{
		if (access(path, F_OK) == 0)
		{
			ft_putendl_fd(": Permission denied", 2);
			return (126);
		}
		ft_putendl_fd(": No such file or directory", 2);
		return (127);
	}
	else
	{
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
}
