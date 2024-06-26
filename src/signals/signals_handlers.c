/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 19:46:56 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/26 20:13:26 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal_number)
{
	(void)signal_number;
	g_o_on = signal_number;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_non_interactive(int signal_number)
{
	(void)signal_number;
	g_o_on = signal_number;
	write(STDOUT_FILENO, "\n", 1);
}

void	handle_sigquit(int signal_number)
{
	(void)signal_number;
	write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
}

void	heredoc_sigint(int signal_number)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	g_o_on = signal_number;
}
