/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:10:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/03 17:11:10 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_unset_env(char *name, char ***env)
{
	int		index;
	int		len;
	char	**new_env;

	len = ft_tablen(*env);
	index = find_env_var_index(name, *env);
	if (index == -1)
		return (*env);
	new_env = allocate_new_env(len);
	if (!new_env)
		return (NULL);
	copy_env_except_index(new_env, *env, index, len);
	free(*env);
	*env = new_env;
	return (*env);
}

static int	unset_single_var(t_token *token, char ***env)
{
	if (my_getenv(token->str, *env))
	{
		if (!ft_unset_env(token->str, env))
			return (-1);
	}
	return (0);
}

int	ft_unset(t_token *token, char ***env)
{
	t_token	*tmp;
	int		ret;

	tmp = token;
	ret = 0;
	while (tmp)
	{
		if (is_operator(tmp) || tmp->type == COMMAND
			|| tmp->type == FILENAME || tmp->type == HEREDOC_FILE)
		{
			tmp = tmp->next->next;
			continue ;
		}
		if (unset_single_var(tmp, env) == -1)
			ret = -1;
		tmp = tmp->next;
	}
	return (ret);
}
