/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 17:28:05 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/31 17:28:05 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_builtins(t_token *token, t_cmd *cmd, int in_pipe)
{
	int		value;

	value = is_builtin(token->str);
	if (value == 1)
		return (ft_echo(token->next));
	else if (value == 2)
		return (ft_cd(token->next, cmd));
	else if (value == 3)
		return (ft_pwd());
	else if (value == 4)
		return (ft_export(token->next, cmd));
	else if (value == 5)
		return (ft_unset(token->next, &(cmd->env)));
	else if (value == 6)
		return (ft_env(cmd->env));
	else if (value == 7)
		return (ft_exit(cmd, token, in_pipe));
	return (0);
}
