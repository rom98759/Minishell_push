/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:09:27 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/03 17:09:34 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
{
	int		i;
	char	*str;

	if (!env)
		return (1);
	i = 0;
	while (env[i])
	{
		str = ft_strchr(env[i], '=');
		if (str != NULL && str + 1 != NULL)
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
