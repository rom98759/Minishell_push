/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:16:29 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 22:07:24 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Récupère le nom de la commande ou quitte en cas d'erreur
 *
 * @param cmd Structure de commande
 * @param index Index de la commande dans la liste
 * @return char* Nom de la commande (alloué)
 */
static char	*get_command_name(t_cmd *cmd, int index)
{
	char	*name;

	name = get_name_command(cmd->token_list, index);
	if (!name)
	{
		ft_free_cmd(cmd, 1);
		exit(1);
	}
	return (name);
}

/**
 * @brief Exécute la commande builtin dans le processus enfant
 *
 * Libère les ressources et quitte avec le code de retour du builtin
 *
 * @param cmd Structure de commande
 * @param index Index de la commande
 * @param name Nom de la commande (déjà alloué)
 */
static void	execute_builtin_child(t_cmd *cmd, int index, char *name)
{
	t_token	*tmp;
	int		builtin_exit_code;

	signal(SIGINT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
	free(name);
	tmp = get_command(cmd->token_list, index);
	builtin_exit_code = ft_execute_builtins(tmp, cmd, 1);
	ft_free_token_list(tmp);
	ft_free_cmd(cmd, 1);
	exit(builtin_exit_code);
}

/**
 * @brief Récupère le chemin exécutable command
 *
 * @param cmd Structure de commande
 * @param name Nom de la commande (alloué)
 * @return char* Chemin de l'exécutable (alloué)
 */
static char	*get_valid_executable_path(t_cmd *cmd, char *name)
{
	char	*path;
	int		exit_code;

	path = get_executable_path(name, cmd->env);
	if (!path)
	{
		exit_code = command_exit(name);
		free(name);
		ft_free_cmd(cmd, 1);
		exit(exit_code);
	}
	return (path);
}

/**
 * @brief Prépare le tableau d'arguments pour execve
 * @param cmd Structure de commande
 * @param index Index de la commande
 * @return char** Tableau d'arguments (alloué)
 */
static char	**command_argv(t_cmd *cmd, int index)
{
	t_token	*current;
	char	**argv;

	current = get_command(cmd->token_list, index);
	if (!current)
		exit(1);
	argv = token_to_tab_sin_redir(current);
	ft_free_token_list(current);
	return (argv);
}

/**
 * @brief Exécute la commande dans le processus enfant
 *
 * Gère les redirections, les builtins et lance execve
 *
 * @param cmd Structure de commande
 * @param index Index de la commande à exécuter
 */
void	run_command(t_cmd *cmd, int index)
{
	char	*name;
	char	*path;
	char	**argv;

	if (handle_redirections(cmd, index) == -1)
	{
		ft_free_cmd(cmd, 1);
		exit(1);
	}
	name = get_command_name(cmd, index);
	if (is_builtin(name))
		execute_builtin_child(cmd, index, name);
	path = get_valid_executable_path(cmd, name);
	free(name);
	argv = command_argv(cmd, index);
	execve(path, argv, cmd->env);
	free(path);
	ft_free_tab(argv);
	ft_free_cmd(cmd, 1);
	perror("minishell execve ");
	exit(1);
}
