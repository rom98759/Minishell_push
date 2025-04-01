/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:15:29 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/21 08:46:22 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Vérifie l'accès à une commande dans les chemins donnés
 *
 * @param paths
 * @param cmd Nom de la commande
 * @return char* Chemin complet de la commande si accessible, NULL sinon
 */
char	*check_access(char **paths, char *cmd)
{
	char	*full_path;
	char	*path_with_slash;
	int		i;

	i = -1;
	while (paths[++i])
	{
		path_with_slash = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_with_slash, cmd);
		free(path_with_slash);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_tab(paths);
			return (full_path);
		}
		free(full_path);
	}
	if (paths)
		ft_free_tab(paths);
	return (NULL);
}

/**
 * @brief Vérifie si un chemin est un répertoire
 *
 * @param path Chemin à vérifier
 * @return int 1 si c'est un répertoire, 0 sinon
 */
int	is_directory(char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == -1)
		return (0);
	if (S_ISDIR(stats.st_mode))
		return (1);
	return (0);
}

/**
 * @brief Récupère le path exécutable pour une commande
 *
 * @param cmd Nom de la commande
 * @param env Environnement
 * @return char* Chemin de l'exécutable, ou NULL si non trouvé
 */
char	*get_executable_path(char *cmd, char **env)
{
	char	**paths;
	char	*path_env;

	if (!cmd || *cmd == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
			return (NULL);
		if (access(cmd, F_OK | X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = my_getenv("PATH", env);
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	return (check_access(paths, cmd));
}
