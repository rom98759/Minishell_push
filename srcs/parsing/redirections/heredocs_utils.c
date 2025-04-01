/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:22:06 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 12:38:43 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_heredoc_to_list(t_heredoc **head, t_heredoc *new_heredoc)
{
	t_heredoc	*tmp;

	if (!new_heredoc)
		return ;
	if (!*head)
	{
		*head = new_heredoc;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_heredoc;
}

static int	read_random_int(int fd)
{
	int	buffer;
	int	bytes_read;

	if (fd == -1)
		return (-1);
	bytes_read = read(fd, &buffer, sizeof(int));
	close(fd);
	if (bytes_read != sizeof(int))
		return (-1);
	return (buffer);
}

char	*generate_file(void)
{
	char	*filename;
	int		random_number;
	int		fd;
	char	*tmp;

	fd = open("/dev/random", O_RDONLY);
	random_number = read_random_int(fd);
	if (random_number == -1)
		return (NULL);
	if (random_number < 0)
		random_number = -random_number;
	tmp = ft_itoa(random_number);
	filename = ft_strjoin(FOLDER_HEREDOC, tmp);
	free(tmp);
	if (access(filename, F_OK) == 0)
	{
		free(filename);
		return (generate_file());
	}
	return (filename);
}

t_heredoc	*get_heredoc(t_heredoc *heredoc, int index)
{
	int			i;
	t_heredoc	*tmp;

	i = 0;
	tmp = heredoc;
	while (tmp && i < index)
	{
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

/**
 * @brief Delete all heredoc files
 * @param heredoc The list of heredoc to delete
 */
void	delete_heredoc(t_heredoc *heredoc)
{
	t_heredoc	*tmp;

	if (!heredoc)
		return ;
	while (heredoc)
	{
		tmp = heredoc;
		heredoc = heredoc->next;
		if (tmp->filename)
		{
			if (access(tmp->filename, F_OK) == 0)
			{
				if (unlink(tmp->filename) == -1)
					perror("minishell: unlink");
			}
			free(tmp->filename);
		}
		if (tmp->delimiter)
			free(tmp->delimiter);
		free(tmp);
	}
}
