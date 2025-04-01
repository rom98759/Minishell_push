/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 11:13:44 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/24 11:51:05 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	expand_env_variable(const char *str, size_t *i,
	t_expansion_data *exp_data, size_t *k)
{
	char	*var_name;
	char	*value;
	size_t	len;

	var_name = get_var_name(str, i);
	if (!*var_name)
	{
		free(var_name);
		exp_data->output_str[*k] = '$';
		*k += 1;
		return (1);
	}
	value = parse_var_value(var_name, exp_data);
	free(var_name);
	if (value)
	{
		len = ft_strlcpy(exp_data->output_str + *k,
				value, exp_data->size - *k + 1);
		*k += len;
		free(value);
		return (len);
	}
	return (0);
}

void	expand_exit_status(t_expansion_data *exp_data, size_t *k, size_t *i)
{
	char	*value;

	value = ft_itoa(exp_data->env_data->last_exit_status);
	*k += ft_strlcpy(exp_data->output_str + *k, value, exp_data->size - *k + 1);
	*i += 1;
	free((char *)value);
}

static int	count_not_empty(const char **str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i][0] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**allocate_and_copy(char **str)
{
	char	**new_str;
	size_t	i;
	size_t	j;

	new_str = ft_calloc(count_not_empty((const char **)str) + 1,
			sizeof(char *));
	if (!new_str)
		return (ft_free_tab(str), NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i][0] != '\0')
		{
			new_str[j] = ft_strdup(str[i]);
			if (!new_str[j])
				return (ft_free_index_tab(new_str, j), ft_free_tab(str), NULL);
			j++;
		}
		i++;
	}
	return (new_str);
}

char	**remove_empty_strings(char **str)
{
	char	**new_str;

	new_str = allocate_and_copy(str);
	ft_free_tab(str);
	return (new_str);
}
