/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe_atoll.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:04:47 by rcaillie          #+#    #+#             */
/*   Updated: 2025/04/01 11:06:12 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calcultate_i(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	return (i);
}

long long	ft_safe_atoll(const char *str, int *valid)
{
	long long	sign;
	long long	res;
	int			i;

	*valid = 1;
	res = 0;
	sign = 1;
	i = calcultate_i(str);
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (res > LLONG_MAX / 10 || (res == LLONG_MAX / 10
				&& (str[i] - '0') > 7 + (sign == -1)))
		{
			*valid = 0;
			return (0);
		}
		res = res * 10 + (str[i++] - '0');
	}
	return (res * sign);
}
