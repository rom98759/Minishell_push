/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:52:38 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/04 16:44:00 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Vérifie si une commande a une redirection de sortie
 *
 * @param tokens Liste de tokens
 * @param i Index de la commande
 * @return int 1 si la commande a une redirection de sortie, 0 sinon
 */
static int	has_stdout_redirection(t_token *tokens, int i)
{
	t_token	*current;
	int		has_output_redirection;
	t_token	*next_node;

	current = get_command(tokens, i);
	has_output_redirection = 0;
	next_node = NULL;
	while (current)
	{
		if (current->type == TRUNC || current->type == APPEND)
		{
			has_output_redirection = 1;
			break ;
		}
		next_node = current->next;
		if (current->str)
			free(current->str);
		free(current);
		current = next_node;
	}
	if (has_output_redirection && current)
		ft_free_token_list(current);
	return (has_output_redirection);
}

/**
 * @brief Exécute les commandes d'un pipeline
 *
 * @param cmd Structure de commande
 * @param i Index de la commande à exécuter
 * @param input_fd Descripteur de fichier d'entrée
 * @param fd Descripteur de fichier du pipe
 * @return int 0 en cas de succès, -1 en cas d'erreur
 */
static void	child_process(t_cmd *cmd, size_t i, int input_fd, int fd[2])
{
	int has_redir;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	close_std(cmd);
	if (input_fd != STDIN_FILENO)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	has_redir = has_stdout_redirection(cmd->token_list, i);
	if (i < cmd->nb_cmd && !has_redir)
		dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	if (has_redir && fd[0] != STDIN_FILENO)
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	run_command(cmd, i);
	exit(0);
}

/**
 * @brief Parent process
 *
 * @param cmd Structure de commande
 * @param i Index de la commande
 * @param fd Descripteur de fichier du pipe
 * @param input_fd Descripteur de fichier d'entrée
 * @param pid PID du processus enfant
 */
static void	parent_process(t_cmd *cmd, size_t i, t_pipe_data *data, pid_t pid)
{
	signal(SIGINT, SIG_IGN);
	if (i < cmd->nb_cmd)
	{
		close(data->fd[1]);
		if (data->input_fd != STDIN_FILENO)
			close(data->input_fd);
		data->input_fd = data->fd[0];
	}
	else
	{
		if (data->input_fd != STDIN_FILENO)
			close(data->input_fd);
		data->last_pid = pid;
	}
}

/**
 * @brief Exécute un pipeline
 *
 * @param cmd Structure de commande
 */
void	execute_pipeline(t_cmd *cmd)
{
	size_t		i;
	pid_t		pid;
	t_pipe_data	data;

	data.input_fd = STDIN_FILENO;
	data.last_pid = -1;
	signal(SIGINT, SIG_IGN);
	i = -1;
	while (++i < cmd->nb_cmd + 1)
	{
		if (i < cmd->nb_cmd && pipe(data.fd) == -1)
			return (ft_putendl_fd("minishell: pipe error creating pipe", 2));
		pid = fork();
		if (pid < 0)
			return (ft_putendl_fd("minishell: fork error fork pipeline", 2));
		else if (pid == 0)
			child_process(cmd, i, data.input_fd, data.fd);
		else
			parent_process(cmd, i, &data, pid);
	}
	get_exit_status(cmd, data.last_pid);
	signal(SIGINT, handle_sigint);
}
