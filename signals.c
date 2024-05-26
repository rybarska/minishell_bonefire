/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:58:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/21 17:58:56 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_eof(t_data *data)
{
	printf("exit\n");
	clean_up_env_vars(data);
	exit_like_a_boss(data, 0);
}

static void	handle_sigint(int signal_number)
{
	(void) signal_number;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigquit(int signal_number)
{
	(void) signal_number;
}

void	set_signal_controls(t_data *data)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
	sigset_t		block_set;

	sigemptyset(&block_set);
	sigaddset(&block_set, SIGTERM);
	sigaddset(&block_set, SIGQUIT);
	sa_int.sa_handler = handle_sigint;
	sa_int.sa_mask = block_set;
	sa_int.sa_flags = 0;
	if (sigaction(SIGINT, &sa_int, NULL) < 0)
		snuff_it(data, "Error: sigaction (sigint) failed\n", NULL, 255);
	sa_quit.sa_handler = handle_sigquit;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = 0;
	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
		snuff_it(data, "Error: sigaction (sigquit) failed\n", NULL, 255);
}
