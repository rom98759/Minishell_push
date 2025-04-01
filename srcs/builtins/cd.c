/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:42:29 by rcaillie          #+#    #+#             */
/*   Updated: 2025/02/17 16:42:29 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_home(t_cmd *cmd, char *pwd)
{
	char	*home;

	home = my_getenv("HOME", cmd->env);
	if (!home)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(pwd);
		return (-1);
	}
	if (chdir(home) == -1)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		free(pwd);
		return (-1);
	}
	return (0);
}

static int	cd_path(char *path, char *pwd)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		free(pwd);
		return (-1);
	}
	return (0);
}

static int	parse_cd_args(t_token *args, t_token **argument)
{
	t_token	*temp;
	int		count;

	*argument = NULL;
	count = 0;
	temp = args;
	while (temp)
	{
		if (temp->type == ARGUMENT)
		{
			count++;
			if (count == 1)
				*argument = temp;
		}
		temp = temp->next;
	}
	if (count > 1)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (-1);
	}
	return (count);
}

int	ft_cd(t_token *args, t_cmd *cmd)
{
	char	*pwd;
	t_token	*argument;
	int		arg_count;

	if (!cmd)
		return (1);
	pwd = get_pwd_raw();
	if (!pwd)
		return (1);
	arg_count = parse_cd_args(args, &argument);
	if (arg_count == -1)
	{
		free(pwd);
		return (1);
	}
	if (arg_count == 0)
	{
		if (cd_home(cmd, pwd) == -1)
			return (1);
	}
	else if (cd_path(argument->str, pwd) == -1)
		return (1);
	if (update_pwd(cmd, pwd) == -1)
		return (1);
	return (0);
}
