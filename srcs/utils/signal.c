/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcaillie <rcaillie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:16:43 by rcaillie          #+#    #+#             */
/*   Updated: 2025/01/30 09:20:04 by rcaillie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static volatile sig_atomic_t	g_sigint_received = 0;

void	handle_sigint(int code)
{
	(void)code;
	g_sigint_received = 1;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_heredoc_sigint(int code)
{
	(void)code;
	g_sigint_received = 1;
	rl_done = 1;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	rl_on_new_line();
	printf("\n");
}

/**
 * @brief Set up the signals
 * SIGINT handle_sigint : Ctrl+C
 * SIGQUIT SIG_IGN : Ctrl+\
 */
void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	reset_sigint(int value)
{
	g_sigint_received = value;
}

int	is_sigint_received(void)
{
	return (g_sigint_received);
}
