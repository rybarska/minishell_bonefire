/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:58:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:30 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

static void	handle_sigint(int signal_number)
{
	(void)signal_number;
	g_o_on = signal_number;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_non_interactive(int signal_number)
{
	(void)signal_number;
	g_o_on = signal_number;
	write(STDOUT_FILENO, "\n", 1);
}

static void	handle_sigquit(int signal_number)
{
	(void)signal_number;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

static void	heredoc_sigint(int signal_number)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_o_on = signal_number;
}

void	set_mode(t_data *data, t_signal_mode mode)
{
	data->signal_mode = mode;
	if (data->signal_mode == INTERACTIVE)
		signal(SIGINT, &handle_sigint);
	else if (data->signal_mode == CHILD)
		signal(SIGINT, SIG_DFL);
	else if (data->signal_mode == NON_INTERACTIVE)
		signal(SIGINT, &handle_sigint_non_interactive);
	else if (data->signal_mode == HERE_DOC)
		signal(SIGINT, &heredoc_sigint);
	if (data->signal_mode == INTERACTIVE)
		signal(SIGQUIT, SIG_IGN);
	else if (data->signal_mode == CHILD)
		signal(SIGQUIT, SIG_DFL);
	else if (data->signal_mode == NON_INTERACTIVE)
		signal(SIGQUIT, &handle_sigquit);
	else if (data->signal_mode == HERE_DOC)
		signal(SIGQUIT, SIG_IGN);
}
