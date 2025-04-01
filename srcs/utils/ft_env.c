/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:14:25 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/20 11:03:02 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Gets the value of an environment variable.
 * @param name The name of the environment variable.
 * @param env The environment variables.
 */
char	*my_getenv(char *name, char **env)
{
	size_t	name_len;

	name_len = ft_strlen(name);
	while (*env)
	{
		if (ft_strncmp(*env, name, name_len) == 0 && (*env)[name_len] == '=')
			return (*env + name_len + 1);
		env++;
	}
	return (NULL);
}

/**
 * Gets the current working directory.
 * @param env The environment variables.
 * @return The current working directory.
 */
char	*get_pwd(char **env)
{
	char	*pwd;
	char	*home;
	char	*result;
	char	*tmp;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
		return (NULL);
	}
	home = my_getenv("HOME", env);
	if (home && ft_strncmp(pwd, home, ft_strlen(home)) == 0)
	{
		tmp = ft_strjoin("~", pwd + ft_strlen(home));
		free(pwd);
		pwd = tmp;
	}
	result = ft_strjoin(pwd, "> ");
	free(pwd);
	return (result);
}

/**
 * Gets the current working directory without pretty print.
 * @param env The environment variables.
 * @return The current working directory.
 */
char	*get_pwd_raw(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		ft_putendl_fd("minishell: pwd: error retrieving current directory", 2);
		return (NULL);
	}
	return (cwd);
}

/**
 * Copies the environment variables.
 * @param env The environment variables.
 * @return A copy of the environment variables.
 */
char	**ft_copy_env(char **env)
{
	int		i;
	int		count;
	char	**new_env;

	i = 0;
	count = ft_tablen(env);
	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			ft_free_tab(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
