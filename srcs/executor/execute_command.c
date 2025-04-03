/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:14:40 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/03 20:37:07 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Exécute le builtin dans le processus parent si applicable.
 *
 * Si le nom de commande est absent ou s'il s'agit d'un builtin et qu'il n'y
 * a qu'une seule commande, le builtin est exécuté ici.
 *
 * @param cmd Structure de commande
 * @param index Index de la commande
 * @return int 1 si un builtin a été exécuté (ou s'il n'y a pas de commande),
 *             0 sinon.
 */
static int	execute_builtin_parent(t_cmd *cmd, int index)
{
	char	*name;
	t_token	*command;

	name = get_name_command(cmd->token_list, index);
	if (!name)
		return (0);
	if (is_builtin(name) && cmd->nb_cmd == 0)
	{
		free(name);
		if (handle_redirections(cmd, index) == -1)
		{
			cmd->exit_code = 1;
			return (1);
		}
		command = get_command(cmd->token_list, index);
		cmd->exit_code = ft_execute_builtins(command, cmd, 0);
		ft_free_token_list(command);
		return (1);
	}
	free(name);
	return (0);
}

/**
 * @brief Attend la fin du processus enfant et met à jour l'exit_code.
 *
 * @param cmd Structure de commande
 * @param pid PID du processus enfant
 */
static void	wait_for_child(t_cmd *cmd, pid_t pid)
{
	int	status;

	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			write(1, "\n", 1);
			cmd->exit_code = WTERMSIG(status) + 128;
		}
		else if (WTERMSIG(status) == SIGQUIT)
		{
			write(1, "Quit\n", 5);
			cmd->exit_code = WTERMSIG(status) + 128;
		}
		reset_sigint(0);
	}
	if (WIFEXITED(status))
		cmd->exit_code = WEXITSTATUS(status);
	signal(SIGINT, handle_sigint);
}

/**
 * @brief Fonction exécutée dans le processus enfant.
 *
 * Configure les signaux puis lance run_command.
 *
 * @param cmd Structure de commande
 * @param index Index de la commande à exécuter
 */
static void	child_process(t_cmd *cmd, int index)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_std(cmd);
	run_command(cmd, index);
	exit(0);
}

/**
 * @brief Exécute la commande (builtin ou externe) en gérant le fork.
 *
 * Si c'est un builtin unique, il est exécuté dans le processus parent.
 * Sinon, on fork et le traitement se fait dans le processus enfant.
 *
 * @param cmd Structure de commande
 * @param index Index de la commande à exécuter
 */
void	execute_command(t_cmd *cmd, int index)
{
	pid_t	pid;

	if (execute_builtin_parent(cmd, index))
		return ;
	pid = fork();
	if (pid == -1)
	{
		ft_putendl_fd("minishell: fork: error forking process", 2);
		return ;
	}
	if (pid == 0)
		child_process(cmd, index);
	else
		wait_for_child(cmd, pid);
}
