/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 16:27:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 16:27:53 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Écrit une ligne dans le fichier
 */
static int	write_line(int fd, char *line, t_cmd *cmd, t_heredoc *heredoc)
{
	char	*expanded_line;

	expanded_line = expand_heredoc(line, heredoc, cmd);
	if (!expanded_line)
		return (-1);
	if (write(fd, expanded_line, ft_strlen(expanded_line)) == -1)
	{
		free(expanded_line);
		return (-1);
	}
	if (write(fd, "\n", 1) == -1)
	{
		free(expanded_line);
		return (-1);
	}
	free(expanded_line);
	return (0);
}

static int	is_sigint_received_heredoc(char *line)
{
	if (is_sigint_received())
	{
		free(line);
		reset_sigint(0);
		return (1);
	}
	return (0);
}

static int	process_heredoc_input(int fd, t_heredoc *heredoc, t_cmd *cmd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf("HEREDOC: unexpected end\n");
			break ;
		}
		if (is_sigint_received_heredoc(line))
			return (1);
		if (is_eof_heredoc(line, heredoc))
		{
			free(line);
			break ;
		}
		if (write_line(fd, line, cmd, heredoc) == -1)
		{
			free(line);
			return (-1);
		}
		free(line);
	}
	return (0);
}

/**
 * @brief Crée un heredoc
 * @param heredoc Structure de heredoc
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
static int	heredoc(t_heredoc *heredoc, t_cmd *cmd)
{
	int	fd;
	int	ret;

	fd = open(heredoc->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell: open");
		return (-1);
	}
	ret = process_heredoc_input(fd, heredoc, cmd);
	close(fd);
	if (ret == -1)
	{
		ft_putendl_fd("minishell: heredoc failed", 2);
		return (-1);
	}
	if (ret == 1)
	{
		cmd->exit_code = 130;
		reset_sigint(0);
		return (-1);
	}
	return (0);
}

/**
 * @brief Crée une liste de heredoc
 * @param cmd Structure de commande
 * @param index Index de la commande
 * @return 0 en cas de succès, -1 en cas d'erreur
 */
int	apply_heredoc(t_cmd *cmd)
{
	t_token	*current;

	current = cmd->token_list;
	if (!current)
		return (-1);
	while (current)
	{
		if (current->type == HEREDOC)
		{
			if (heredoc(get_heredoc(cmd->heredoc_list,
						cmd->i_heredoc), cmd) == -1)
				return (-1);
			cmd->i_heredoc++;
		}
		current = current->next;
	}
	cmd->i_heredoc = 0;
	return (0);
}
