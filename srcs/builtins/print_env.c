/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:20:28 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/26 12:13:58 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sort_env(char **env)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static	int	var_not_to_print(char *var, int *i)
{
	if (ft_strncmp(var, "_=", 2) == 0)
	{
		(*i)++;
		return (1);
	}
	(void)i;
	return (0);
}

void	ft_print_sorted_env(char **env)
{
	int		i;
	char	*equal;

	ft_sort_env(env);
	i = 0;
	while (env[i])
	{
		if (var_not_to_print(env[i], &i))
			continue ;
		equal = ft_strchr(env[i], '=');
		printf("declare -x ");
		if (equal)
		{
			*equal = '\0';
			printf("%s=\"%s\"", env[i], equal + 1);
			*equal = '=';
		}
		else
		{
			printf("%s", env[i]);
		}
		printf("\n");
		i++;
	}
}
