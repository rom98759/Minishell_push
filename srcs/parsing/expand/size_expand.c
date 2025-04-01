/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 17:39:35 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 20:21:48 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_var_size(const char *str, t_expand *exp_data, size_t *i)
{
	char	*var_name;
	char	*value;
	size_t	size;

	var_name = get_var_name(str, i);
	if (!*var_name)
	{
		free(var_name);
		return (1);
	}
	value = parse_var_value(var_name, exp_data);
	size = ft_strlen(value);
	free(var_name);
	free(value);
	return (size);
}

size_t	count_new_size(const char *str, t_expand *exp_data)
{
	size_t	i;
	size_t	size;

	i = 0;
	size = 0;
	while (str[i])
	{
		exp_data->quote = handle_quotes(str[i], exp_data->quote);
		if (str[i] == '$' && exp_data->quote != 1)
		{
			i++;
			if (str[i] == '?')
				size += ft_itoa_len(exp_data->env_data->last_exit_status);
			else
				size += get_var_size(str, exp_data, &i);
		}
		else
		{
			size++;
			i++;
		}
	}
	exp_data->quote = 0;
	return (size);
}
