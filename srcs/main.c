/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 11:48:14 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 11:15:10 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_signal(t_cmd *cmd)
{
	if (is_sigint_received())
	{
		cmd->exit_code = 130;
		reset_sigint(0);
	}
}

/**
 * @brief Process input check line
 * @param cmd Command structure
 * @param line Input line to process (malloc) (free by ft_subcmd)
 * @return 1 if success, 0 if error
 */
static int	process_line(t_cmd *cmd, char *line)
{
	char	**cmd_parts;

	if (ft_strlen(line) == 0 || is_full_whitespace(line))
	{
		free(line);
		return (0);
	}
	cmd_parts = ft_subcmd(line);
	if (!syntax_error(cmd_parts, cmd))
	{
		ft_free_tab(cmd_parts);
		return (0);
	}
	if (tokenize_and_validate(cmd_parts, cmd) == -1 && !cmd->token_list)
	{
		ft_free_token_list(cmd->token_list);
		return (0);
	}
	cmd->nb_cmd = get_command_count(cmd->token_list);
	return (1);
}

/**
 * @brief Execute the parsed command
 * @param cmd Command structure
 * @return 1 if success, 0 if error
 */
static int	execute_parsed_command(t_cmd *cmd)
{
	cmd->i_heredoc = 0;
	if (handle_heredocs(cmd) == -1)
	{
		ft_free_cmd(cmd, 0);
		return (0);
	}
	if (save_std(cmd) == -1)
	{
		ft_free_cmd(cmd, 1);
		ft_exit_error("Save std failed", 1);
	}
	if (cmd->nb_cmd == 0)
		execute_command(cmd, 0);
	else
		execute_pipeline(cmd);
	if (restore_std(cmd) == -1)
	{
		ft_free_cmd(cmd, 1);
		ft_exit_error("Restore std failed", 1);
	}
	ft_free_cmd(cmd, 0);
	return (1);
}

/**
 * @brief Main function of the shell
 * @param env Environment variables
 */
void	ft_exec(char **env)
{
	char	*line;
	t_cmd	*cmd;

	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		ft_exit_error("Malloc failed", 1);
	ft_bzero(cmd, sizeof(t_cmd));
	cmd->env = env;
	while (1)
	{
		cmd->i_heredoc = 0;
		line = ft_getline(cmd->env);
		if (!line)
			break ;
		check_signal(cmd);
		if (!process_line(cmd, line))
			continue ;
		if (!execute_parsed_command(cmd))
			continue ;
	}
	ft_free_cmd(cmd, 1);
	printf("exit\n");
}

int	main(int ac, char **av, char **env)
{
	char	**env_cpy;

	(void)ac;
	(void)av;
	env_cpy = ft_copy_env(env);
	if (!env_cpy)
		ft_exit_error("Malloc failed", 1);
	setup_signals();
	ft_read_history();
	ft_exec(env_cpy);
	return (0);
}
