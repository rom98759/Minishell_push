/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:12:37 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 10:59:40 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "get_next_line.h"
# include "expand.h"

/* ************************************************************************** */
/*                               DEFINES & MACROS                             */
/* ************************************************************************** */

# define FOLDER_HEREDOC "/tmp/heredoc_"

/* ************************************************************************** */
/*                                STRUCTURES                                  */
/* ************************************************************************** */

typedef enum e_token_type
{
	TRUNC,
	APPEND,
	INPUT,
	HEREDOC,
	PIPE,
	COMMAND,
	ARGUMENT,
	FILENAME,
	HEREDOC_FILE,
	UNKNOWN_OPERATOR
}				t_token_type;

typedef struct s_token
{
	char			*str;
	int				type;
	int				id;
	struct s_token	*next;
}				t_token;

typedef struct s_pipe_data
{
	int			fd[2];
	int			input_fd;
	pid_t		last_pid;
}				t_pipe_data;

typedef struct s_stdcopy
{
	int				stdin_copy;
	int				stdout_copy;
	int				stderr_copy;
}				t_stdcopy;

typedef struct s_redir
{
	int				type;
	char			*filename;
	int				fd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_heredoc
{
	char				*filename;
	char				*delimiter;
	struct s_heredoc	*next;
}				t_heredoc;

typedef struct s_cmd
{
	char			**env;
	size_t			exit_code;
	t_token			*token_list;
	size_t			index;
	size_t			nb_cmd;
	t_stdcopy		*stdcopy;
	t_redir			*redir_list;
	t_heredoc		*heredoc_list;
	size_t			i_heredoc;
}				t_cmd;

/* ************************************************************************** */
/*                               FUNCTION PROTOTYPES                          */
/* ************************************************************************** */

/*
**                          TOKENS MANAGEMENT
*/
int			is_operator(t_token *token);
size_t		get_token_count(t_token *tokens);
t_token		*tokenize(char **input);
int			tokenize_and_validate(char **input, t_cmd *cmd);
void		detect_and_add_redirections(t_token *tokens, t_cmd *cmd);
size_t		get_command_count(t_token *tokens);
char		*get_new_str_token(char *s, int type);
char		**token_to_tab_sin_redir(t_token *tokens);

/*
**                        GET COMMAND TOKENS
*/
t_token		*get_command(t_token *tokens, int indice);
char		*get_name_command(t_token *token, int indice);

/*
**                        DETECTION & VALIDATION
*/
int			detect_redirections(char *str);
int			get_token_type(char **input, int i);
void		detect_commands_and_arguments(t_token *tokens);
void		detect_filenames(t_token *tokens);
int			is_valid_token_type(int type);
int			is_valid_filename(char *str);
int			is_valid_command(char *str);
int			handle_pipe_syntax(t_token *current, t_token *tokens, t_cmd *cmd);
int			handle_redirection_syntax(t_token *current, t_cmd *cmd);
int			handle_filename_syntax(t_token *current, t_token *tokens,
				t_cmd *cmd);
int			validate_syntax(t_token *tokens, t_cmd *cmd);

/*
**                          SPLIT ARGS
*/
char		**ft_subcmd(char *cmd);
int			is_op_split(char *s);
void		skip_whitespace(char *cmd, int *i);
void		handle_quote(char *cmd, int *i, char quote);
char		*dup_word(char *str, int start, int end);
int			check_cmd(t_token **new_line, t_token **cur, int *flag,
				t_token **p);
int			check_doc(t_token **cur, t_token **p, t_token *start);
int			check_arg(t_token **cur, t_token *start, t_token **p);
int			check_trunc(t_token **cur, t_token *start, t_token **p);
int			check_pipe(t_token **cur, t_token **p, t_token **start);

/*
**                          TOKENS UTILS
*/
t_token		*create_token(char *str, int type);
void		add_token_to_list(t_token **head, t_token *new_token);
t_token		*swap_token(t_cmd *cmd);

/*
**                             EXIT & ERROR
*/
void		ft_update_exit_code(t_cmd *cmd, int status, char *msg);
void		ft_exit_free_cmd(t_cmd *cmd, int exit_code);
void		ft_exit_error(char *msg, int exit_code);
int			handle_error(char *message, int exit_code, t_cmd *cmd);
int			syntax_error(char **tab, t_cmd *cmd);

/*
**                               MEMORY & FREE
*/
void		ft_free_tab(char **tab);
void		ft_free_cmd(t_cmd *cmd, int free_cmd);
void		ft_free_index_tab(char **tab, int index);
void		ft_free_token_list(t_token *head);
void		ft_free_redir_list(t_redir *list);

/*
**                                UTILS
*/
size_t		ft_tablen(char **tab);
int			is_whitespace(char c);
int			is_full_whitespace(char *str);
size_t		ft_itoa_len(int n);
char		*remove_quotes(char *str);
char		*remove_all_quote(char *s);
long long	ft_safe_atoll(const char *str, int *valid);

/*
**                                HEREDOC
*/
int			handle_heredocs(t_cmd *cmd);
int			create_heredoc(t_cmd *cmd);
int			apply_heredoc(t_cmd *cmd);
int			is_eof_heredoc(char *line, t_heredoc *heredoc);
char		*generate_file(void);
char		*expand_heredoc(char *line, t_heredoc *heredoc, t_cmd *cmd);
void		add_heredoc_to_list(t_heredoc **head, t_heredoc *new_heredoc);
void		delete_heredoc(t_heredoc *heredoc);
void		change_heredoc_to_input(t_cmd *cmd);
t_heredoc	*get_heredoc(t_heredoc *heredoc, int index);

/*
**                                HISTORY
*/
void		ft_save_history(char *line);
void		ft_read_history(void);

/*
**                      ENVIRONMENT FUNCTIONS
*/
char		*my_getenv(char *name, char **env);
char		*get_pwd(char **env);
char		*get_pwd_raw(void);
char		**ft_copy_env(char **env);

/*
**                          SIGNAL HANDLERS
*/
void		setup_signals(void);
void		handle_sigint(int code);
void		handle_heredoc_sigint(int code);
int			is_sigint_received(void);
void		reset_sigint(int value);

/*
**                          REDIRECTIONS
*/
int			handle_redirections(t_cmd *cmd, int index);
void		create_redir(t_cmd *cmd, int index);
int			apply_redirections(t_cmd *cmd);

/*
**                             EXECUTION
*/
char		*get_executable_path(char *cmd, char **env);
void		execute_command(t_cmd *cmd, int index);
void		execute_pipeline(t_cmd *cmd);
void		get_exit_status(t_cmd *cmd, int last_pid);
void		run_command(t_cmd *cmd, int index);
int			command_exit(char *path);
int			is_directory(char *path);

/*
**                             BUILTINS
*/
int			is_builtin(char *str);
int			ft_execute_builtins(t_token *token, t_cmd *cmd, int in_pipe);
int			ft_exit(t_cmd *cmd, t_token *tokens, int in_pipe);
int			ft_cd(t_token *args, t_cmd *cmd);
int			update_oldpwd(t_cmd *cmd, char *old_pwd);
int			update_pwd(t_cmd *cmd, char *old_pwd);
int			ft_echo(t_token *token);
int			ft_env(char **env);
int			ft_export(t_token *token, t_cmd *cmd);
int			ft_add_env(char *name, char *value, char ***env);
int			is_valid_export(char *str);
char		**ft_realloc_env(char **env);
int			extract_and_clean_value(char **value);
char		*create_env_entry(char *name, char *value);
int			is_append(char *name);
int			handle_existing_env(char *name, char *value, char ***env, int i);
int			add_new_env(char *name, char *value, char ***env, int i);
void		ft_print_sorted_env(char **env);
int			ft_pwd(void);
int			ft_unset(t_token *token, char ***env);
int			find_env_var_index(char *name, char **env);
char		**allocate_new_env(int len);
void		copy_env_except_index(char **new_env, char **env,
				int index, int len);

/*
**                                 MAIN
*/
char		*ft_readline(char *prompt);
char		*ft_getline(char **env);
void		ft_exec(char **env);

/*
**                                STD
*/
int			save_std(t_cmd *cmd);
int			restore_std(t_cmd *cmd);
void		close_std(t_cmd *cmd);

#endif
