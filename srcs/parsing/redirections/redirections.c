/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 11:20:45 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/06 17:38:22 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_file(t_redir *redir)
{
	int	fd;

	fd = -1;
	if (!redir->filename)
		return (-1);
	if (redir->type == TRUNC)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir->type == APPEND)
		fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->filename, O_RDONLY);
	return (fd);
}

/**
 * * @brief Apply redirections to the command
 * * @param cmd Command structure
 * * @return 0 on success, -1 on error
 */
int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		fd;

	redir = cmd->redir_list;
	while (redir)
	{
		fd = open_file(redir);
		if (fd == -1)
		{
			perror("minishell open ");
			return (-1);
		}
		if (redir->type == INPUT)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		redir->fd = fd;
		redir = redir->next;
	}
	return (0);
}

/**
 * @brief Create redirections from the command
 * @param cmd Command structure
 * @param index Index of the command in the pipeline
 * @return 0 on success, -1 on error
 */
int	handle_redirections(t_cmd *cmd, int index)
{
	create_redir(cmd, index);
	if (cmd->redir_list)
		if (apply_redirections(cmd) == -1)
			return (-1);
	return (0);
}
