/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 19:54:31 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 19:54:31 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains_quotes(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

char	*expand_var_heredoc(char *str, char **env, int last_exit_status)
{
	t_expand	exp_data;
	char		*new_str;

	exp_data = init_exp_data(env, last_exit_status);
	if (!exp_data.env_data)
		return (NULL);
	exp_data.size = count_new_size(str, &exp_data);
	new_str = expand_single_char(str, &exp_data);
	if (!new_str)
	{
		free(exp_data.env_data);
		return (NULL);
	}
	free(exp_data.env_data);
	return (new_str);
}

char	*expand_heredoc(char *line, t_heredoc *heredoc, t_cmd *cmd)
{
	char	*line_copy;

	line_copy = NULL;
	if (contains_quotes(heredoc->delimiter) == 1)
		return (ft_strdup(line));
	else
	{
		line_copy = expand_var_heredoc(line, cmd->env, cmd->exit_code);
		if (!line_copy)
		{
			ft_putendl_fd("minishell: expand malloc failed", 2);
			return (NULL);
		}
	}
	return (line_copy);
}
