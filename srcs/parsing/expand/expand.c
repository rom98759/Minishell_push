/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:24:36 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/20 11:24:36 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_single_char(const char *str, t_expand *exp_data)
{
	size_t	i;
	size_t	k;

	exp_data->output_str = ft_calloc(exp_data->size + 1, sizeof(char));
	if (!exp_data->output_str)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		exp_data->quote = handle_quotes(str[i], exp_data->quote);
		if (str[i] == '$' && exp_data->quote != 1)
		{
			i++;
			if (str[i] == '?')
				expand_exit_status(exp_data, &k, &i);
			else
				expand_env_variable(str, &i, exp_data, &k);
		}
		else
			exp_data->output_str[k++] = str[i++];
	}
	return (exp_data->output_str);
}

t_expand	init_exp_data(char **env, int last_exit_status)
{
	t_expand	exp_data;

	exp_data.env_data = (t_env_data *)ft_calloc(1, sizeof(t_env_data));
	if (!exp_data.env_data)
		return (exp_data);
	exp_data.env_data->env = env;
	exp_data.env_data->last_exit_status = last_exit_status;
	exp_data.quote = 0;
	return (exp_data);
}

char	**expand_var(char **str, char **env, int last_exit_status)
{
	size_t		i;
	char		**new_str;
	t_expand	exp_data;

	exp_data = init_exp_data(env, last_exit_status);
	i = ft_tablen(str);
	new_str = ft_calloc(i + 1, sizeof(char *));
	if (!new_str)
		return (NULL);
	i = -1;
	while (str[++i])
	{
		exp_data.input_str = str[i];
		exp_data.size = count_new_size(str[i], &exp_data);
		new_str[i] = expand_single_char(str[i], &exp_data);
		if (!new_str[i])
		{
			free(exp_data.env_data);
			ft_free_index_tab(new_str, i);
			return (NULL);
		}
	}
	free(exp_data.env_data);
	new_str = remove_empty_strings(new_str);
	return (new_str);
}
