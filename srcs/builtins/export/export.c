/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:02:35 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 16:45:57 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	extract_name_value(char *token_str, char **name, char **value)
{
	char	*equal_sign;

	equal_sign = ft_strchr(token_str, '=');
	if (!equal_sign)
	{
		ft_putendl_fd("minishell: not a valid identifier", 2);
		return (1);
	}
	*name = ft_substr(token_str, 0, equal_sign - token_str);
	*value = ft_strdup(equal_sign + 1);
	if (!*name || !*value || extract_and_clean_value(value))
	{
		free(*name);
		free(*value);
		return (1);
	}
	return (0);
}

static int	process_export_token(char *token_str, char ***env)
{
	char	*name;
	char	*value;

	if (extract_name_value(token_str, &name, &value))
		return (1);
	if (ft_add_env(name, value, env))
	{
		free(name);
		free(value);
		return (1);
	}
	free(name);
	free(value);
	return (0);
}

static int	process_export_tokens(t_token *token, char ***new_env)
{
	while (token)
	{
		if (is_operator(token) || token->type == COMMAND
			|| token->type == FILENAME || token->type == HEREDOC_FILE)
		{
			token = token->next->next;
			continue ;
		}
		if (!is_valid_export(token->str))
		{
			token = token->next;
			continue ;
		}
		if (ft_strchr(token->str, '='))
		{
			if (process_export_token(token->str, new_env))
				return (1);
		}
		else if (ft_add_env(token->str, NULL, new_env))
			return (1);
		token = token->next;
	}
	return (0);
}

static int	valid_export(t_token *token)
{
	int		valid;

	valid = 0;
	while (token)
	{
		if (is_operator(token) || token->type == COMMAND
			|| token->type == FILENAME || token->type == HEREDOC_FILE)
		{
			token = token->next->next;
			continue ;
		}
		if (!is_valid_export(token->str))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(token->str, 2);
			ft_putendl_fd("': not a valid identifier", 2);
			valid = 1;
		}
		token = token->next;
	}
	return (valid);
}

int	ft_export(t_token *token, t_cmd *cmd)
{
	char	**new_env;

	if (!token)
	{
		ft_print_sorted_env(cmd->env);
		return (0);
	}
	new_env = ft_copy_env(cmd->env);
	if (!new_env)
		return (1);
	if (process_export_tokens(token, &new_env))
	{
		ft_free_tab(new_env);
		return (1);
	}
	ft_free_tab(cmd->env);
	cmd->env = new_env;
	return (valid_export(token));
}
