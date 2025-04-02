/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 10:15:49 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/02 13:00:20 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_env_var_index(char *name, char **env)
{
	int	i;
	int	len;

	len = ft_tablen(env);
	i = 0;
	while (i < len)
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0
			&& (env[i][ft_strlen(name)] == '='
			|| env[i][ft_strlen(name)] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

char	**allocate_new_env(int len)
{
	char	**new_env;

	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (NULL);
	return (new_env);
}

void	copy_env_except_index(char **new_env, char **env,
		int index, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < len)
	{
		if (i != index)
		{
			new_env[j] = env[i];
			j++;
		}
		else
			free(env[i]);
		i++;
	}
	new_env[j] = NULL;
}
