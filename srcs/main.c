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






char	*get_type(int type)
{
	if (type == TRUNC)
		return ("TRUNC");
	if (type == APPEND)
		return ("APPEND");
	if (type == INPUT)
		return ("INPUT");
	if (type == HEREDOC)
		return ("HEREDOC");
	if (type == PIPE)
		return ("PIPE");
	if (type == COMMAND)
		return ("COMMAND");
	if (type == ARGUMENT)
		return ("ARGUMENT");
	if (type == FILENAME)
		return ("FILENAME");
	if (type == HEREDOC_FILE)
		return ("HEREDOC_FILE");
	return ("UNKNOWN");
}

char	*get_color(int type)
{
	if (type == TRUNC)
		return ("\033[0;31m");
	if (type == APPEND)
		return ("\033[0;32m");
	if (type == INPUT)
		return ("\033[0;33m");
	if (type == HEREDOC)
		return ("\033[0;34m");
	if (type == PIPE)
		return ("\033[0;35m");
	if (type == COMMAND)
		return ("\033[0;36m");
	if (type == ARGUMENT)
		return ("\033[0;37m");
	if (type == FILENAME)
		return ("\033[1;33m");
	if (type == HEREDOC_FILE)
		return ("\033[1;34m");
	return ("\033[0m");
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = tokens;
	while (current)
	{
		printf("%sToken: %s (type: %s) id: %d Current Adresse: %p\033[0m\n",
			get_color(current->type),
			current->str,
			get_type(current->type),
			current->id,
			current);
		current = current->next;
	}
	while (i < 50)
	{
		printf("-");
		i++;
	}
	printf("\n");
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

	printf("token_list \n");
	print_tokens(cmd->token_list);

	cmd->token_list = swap_token(cmd);


	printf("token_list NEW \n");
	print_tokens(cmd->token_list);
	ft_free_token_list(cmd->token_list);
	cmd->token_list = NULL;
	return (0);

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
			break ; //////////////////////////////////// CONTINUE
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
