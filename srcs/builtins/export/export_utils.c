/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:02:48 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/25 14:15:41 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_export(char *str)
{
	if (!str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	while (*str)
	{
		if (*str == '=')
			return (1);
		if (*str == '+')
		{
			if (*(str + 1) == '=')
				return (1);
			return (0);
		}
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}

static char	**allocate_new_env2(char **env)
{
	size_t	count;
	char	**new_env;

	count = ft_tablen(env);
	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (NULL);
	return (new_env);
}

char	**ft_realloc_env(char **env)
{
	size_t	i;
	char	**new_env;

	i = 0;
	new_env = allocate_new_env2(env);
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new_env[i] = NULL;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

int	extract_and_clean_value(char **value)
{
	char	*tmp;

	if (((*value)[0] == '"' && (*value)[ft_strlen(*value) - 1] == '"') ||
		((*value)[0] == '\'' && (*value)[ft_strlen(*value) - 1] == '\''))
	{
		tmp = *value;
		*value = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
		free(tmp);
		if (!*value)
			return (1);
	}
	return (0);
}
