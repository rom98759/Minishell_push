/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:35:40 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/15 19:35:40 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

/*
** Structure contenant les données d'environnement.
*/
typedef struct s_env_data
{
	char	**env;
	int		last_exit_status;
}				t_env_data;

/*
** Structure utilisée pour la gestion de l'expansion des variables.
*/
typedef struct s_expansion_data
{
	t_env_data	*env_data;
	char		*input_str;
	char		*output_str;
	size_t		size;
	int			quote;
}				t_expand;

/*
** Prototypes de fonctions d'expansion.
*/
char		*clean_whitespace(const char *str);
char		*parse_var_value(char *var_name, t_expand *exp_data);
int			handle_quotes(char c, int quote);
size_t		get_var_size(const char *str, t_expand *exp_data, size_t *i);
size_t		count_new_size(const char *str, t_expand *exp_data);
void		expand_exit_status(t_expand *exp_data, size_t *k, size_t *i);
size_t		expand_env_variable(const char *str, size_t *i,
				t_expand *exp_data, size_t *k);
char		*expand_single_char(const char *str, t_expand *exp_data);
char		**expand_var(char **str, char **env, int last_exit_status);
char		*get_var_name(const char *str, size_t *i);
char		**remove_empty_strings(char **str);
t_expand	init_exp_data(char **env, int last_exit_status);

#endif