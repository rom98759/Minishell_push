/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_update.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 17:00:33 by rcaillie          #+#    #+#             */
/*   Updated: 2025/03/31 17:00:33 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_oldpwd(t_cmd *cmd, char *old_pwd)
{
	t_token	*old_pwd_token;

	if (!cmd || !old_pwd)
		return (-1);
	if (my_getenv("OLDPWD", cmd->env))
	{
		old_pwd_token = create_token(ft_strjoin("OLDPWD=", old_pwd), ARGUMENT);
		if (!old_pwd_token || ft_export(old_pwd_token, cmd))
		{
			free(old_pwd);
			ft_free_token_list(old_pwd_token);
			return (-1);
		}
		ft_free_token_list(old_pwd_token);
	}
	free(old_pwd);
	return (0);
}

int	update_pwd(t_cmd *cmd, char *old_pwd)
{
	char	*pwd;
	t_token	*pwd_token;

	if (!cmd || !old_pwd)
		return (-1);
	pwd = get_pwd_raw();
	if (!pwd)
		return (-1);
	if (my_getenv("PWD", cmd->env))
	{
		pwd_token = create_token(ft_strjoin("PWD=", pwd), ARGUMENT);
		if (!pwd_token || ft_export(pwd_token, cmd))
		{
			free(pwd);
			free(old_pwd);
			ft_free_token_list(pwd_token);
			return (-1);
		}
		ft_free_token_list(pwd_token);
	}
	if (update_oldpwd(cmd, old_pwd) == -1)
		return (-1);
	free(pwd);
	return (0);
}
