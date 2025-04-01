/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_concat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 11:01:13 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/26 11:19:29 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_append(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (name[len - 1] == '+')
	{
		name[len - 1] = '\0';
		return (1);
	}
	return (0);
}

static char	*append_value(char *old_entry, char *value)
{
	char	*old_value;
	char	*new_val;
	char	*temp;

	temp = ft_strchr(old_entry, '=');
	if (temp)
		old_value = temp + 1;
	else
		old_value = "";
	new_val = ft_strjoin(old_value, value);
	free(old_entry);
	return (new_val);
}

int	handle_existing_env(char *name, char *value, char ***env, int i)
{
	char	*new_val;

	new_val = append_value((*env)[i], value);
	if (!new_val)
		return (1);
	(*env)[i] = create_env_entry(name, new_val);
	free(new_val);
	return (0);
}

int	add_new_env(char *name, char *value, char ***env, int i)
{
	char	**new_env;

	new_env = ft_realloc_env(*env);
	if (!new_env)
		return (1);
	*env = new_env;
	new_env[i] = create_env_entry(name, value);
	if (!new_env[i])
		return (1);
	new_env[i + 1] = NULL;
	return (0);
}
