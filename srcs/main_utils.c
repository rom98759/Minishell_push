/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:14:11 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 17:14:11 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *prompt)
{
	char	*line;
	char	*temp_prompt;

	temp_prompt = ft_strjoin("\1\033[1;36m\2", prompt);
	if (!temp_prompt)
		return (NULL);
	prompt = ft_strjoin(temp_prompt, "\1\033[0m\2");
	free(temp_prompt);
	if (!prompt)
		return (NULL);
	line = readline(prompt);
	free(prompt);
	if (!line)
		return (NULL);
	ft_save_history(line);
	return (line);
}

char	*ft_getline(char **env)
{
	char	*line;
	char	*cwd;

	cwd = get_pwd(env);
	if (!cwd)
		return (NULL);
	line = ft_readline(cwd);
	free(cwd);
	return (line);
}
