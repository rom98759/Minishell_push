/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:58:45 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/23 11:26:25 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Save history in file
void	ft_save_history(char *line)
{
	int	fd;

	if (ft_strlen(line) <= 0 || ft_strncmp(line, "\n", 1) == 0)
		return ;
	add_history(line);
	fd = open(".minishell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd < 0)
		return ;
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	close(fd);
}

// Read history from file
void	ft_read_history(void)
{
	int		fd;
	char	*line;
	char	*tmp;

	fd = open(".minishell_history", O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strtrim(line, "\n");
		add_history(tmp);
		free(line);
		free(tmp);
		line = get_next_line(fd);
	}
	close(fd);
}
