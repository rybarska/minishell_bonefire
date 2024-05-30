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

#include "include/minishell.h"

static void	handle_sigint(int signal_number)
{
	(void)signal_number;
	//g_o_on = signal_number;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	heredoc_sigint(int signal_number)
{
	//(void)signal_number;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	//write(STDOUT_FILENO, "\n", 1);
	printf("number is: %d\n", signal_number);
	g_o_on = signal_number;//86;
}

// static void	handle_sigquit(int signal_number)
// {
// 	g_o_on = signal_number;
// }

void	set_signal_controls(t_data *data)
{
	
	if (data->signal_mode == INTERACTIVE)
		signal(SIGINT, &handle_sigint);
	else if (data->signal_mode == CHILD)
		signal(SIGINT, SIG_DFL);
	else if (data->signal_mode == NON_INTERACTIVE)
		signal(SIGINT, SIG_IGN);
	else if (data->signal_mode == HERE_DOC)
		signal(SIGINT, &heredoc_sigint);

	if (data->signal_mode == INTERACTIVE)
		signal(SIGQUIT, SIG_IGN);
	else if (data->signal_mode == CHILD)
		signal(SIGQUIT, SIG_DFL);
	else if (data->signal_mode == NON_INTERACTIVE)
		signal(SIGQUIT, SIG_IGN);
	else if (data->signal_mode == HERE_DOC)
		signal(SIGQUIT, SIG_IGN);
}

// void	set_signal_controls(t_data *data)
// {
// 	struct sigaction	sa_int;
// 	struct sigaction	sa_quit;
	
// 	sigemptyset(&sa_int.sa_mask);
// 	if (data->signal_mode == INTERACTIVE)
// 		sa_int.sa_sigaction = &handle_sigint;
// 	else if (data->signal_mode == CHILD)
// 		sa_int.sa_handler = SIG_DFL;
// 	else if (data->signal_mode == NON_INTERACTIVE)
// 		sa_int.sa_handler = SIG_IGN;
// 	sa_int.sa_flags = SA_RESTART;
// 	if (sigaction(SIGINT, &sa_int, NULL) < 0)
// 		snuff_it(data, "Error: sigaction (sigint) failed\n", NULL, 255);
// 	sigemptyset(&sa_quit.sa_mask);
// 	if (data->signal_mode == INTERACTIVE || NON_INTERACTIVE)
// 		sa_quit.sa_handler = SIG_IGN;
// 	else if (data->signal_mode == CHILD)
// 		sa_quit.sa_handler = SIG_DFL; //TODO: print quit core dumped
// 	sa_quit.sa_flags = SA_RESTART;
// 	if (sigaction(SIGQUIT, &sa_quit, NULL) < 0)
// 		snuff_it(data, "Error: sigaction (sigquit) failed\n", NULL, 255);
// }

void	set_mode(t_data *data, t_signal_mode mode)
{
	data->signal_mode = mode;
	set_signal_controls(data);
}
