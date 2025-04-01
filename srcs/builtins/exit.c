/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:14:54 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/06 16:05:31 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_str_is_numeric(char *str)
{
	int	i;
	int	valid;

	valid = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (ft_safe_atoll(str, &valid) > -9223372036854775807 && valid == 0)
	{
		free(str);
		return (0);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			free(str);
			return (0);
		}
		i++;
	}
	free(str);
	return (1);
}

static int	ft_exit_and_free(t_cmd *cmd, t_token *tokens, char **args, int code)
{
	ft_free_tab(args);
	ft_free_token_list(tokens);
	ft_exit_free_cmd(cmd, code);
	return (code);
}

static int	handle_empty_args(t_cmd *cmd, t_token *tokens,
		char **args, int in_pipe)
{
	if (in_pipe == 0)
		printf("exit\n");
	return (ft_exit_and_free(cmd, tokens, args, cmd->exit_code));
}

static int	handle_invalid_numeric(t_cmd *cmd, t_token *tokens,
		char **args, int in_pipe)
{
	if (in_pipe == 0)
		printf("exit\n");
	ft_putendl_fd("minishell: exit: numeric argument required", 2);
	return (ft_exit_and_free(cmd, tokens, args, 2));
}

int	ft_exit(t_cmd *cmd, t_token *tokens, int in_pipe)
{
	char	**args;

	restore_std(cmd);
	delete_heredoc(cmd->heredoc_list);
	cmd->heredoc_list = NULL;
	args = token_to_tab_sin_redir(tokens->next);
	if (!args || !args[0])
		return (handle_empty_args(cmd, tokens, args, in_pipe));
	if (!ft_str_is_numeric(remove_quotes(args[0])))
		return (handle_invalid_numeric(cmd, tokens, args, in_pipe));
	if (args[1])
	{
		if (in_pipe == 0)
			printf("exit\n");
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		ft_free_tab(args);
		return (1);
	}
	if (in_pipe == 0)
		printf("exit\n");
	return (ft_exit_and_free(cmd, tokens, args, ft_atoi(args[0]) % 256));
}
