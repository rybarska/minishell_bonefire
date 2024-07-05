/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 17:58:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/04 21:25:27 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_signal_controls(t_data *data)
{
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

void	set_mode(t_data *data, t_signal_mode mode)
{
	data->signal_mode = mode;
	set_signal_controls(data);
}
