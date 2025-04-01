/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:17:53 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/26 11:17:50 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*generate_env_entry(char *entry, char *value)
{
	char	*tmp;

	tmp = entry;
	entry = ft_strjoin(entry, value);
	free(tmp);
	return (entry);
}

char	*create_env_entry(char *name, char *value)
{
	char	*entry;

	if (value)
		entry = ft_strjoin(name, "=");
	else
		entry = ft_strdup(name);
	if (!entry || !value)
		return (entry);
	return (generate_env_entry(entry, value));
}

static int	update_existing_env(char *name, char *value, char ***env, int i)
{
	char	*new_env_entry;

	if (!value)
		return (0);
	free((*env)[i]);
	new_env_entry = create_env_entry(name, value);
	if (!new_env_entry)
		return (1);
	(*env)[i] = new_env_entry;
	return (0);
}

int	ft_add_env(char *name, char *value, char ***env)
{
	int			i;
	size_t		name_len;
	int			append;

	append = is_append(name);
	name_len = ft_strlen(name);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], name, name_len) == 0 &&
			(((*env)[i][name_len] == '=' || (*env)[i][name_len] == '\0')))
		{
			if (append)
				return (handle_existing_env(name, value, env, i));
			else
				return (update_existing_env(name, value, env, i));
		}
		i++;
	}
	return (add_new_env(name, value, env, i));
}
