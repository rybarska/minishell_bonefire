/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:56:19 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/14 21:56:21 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fd_set_minus1(int *fd)
{
	if (fd != NULL && *fd != -1)
	{
		if (close(*fd) < 0)
			perror("file descriptor");
		*fd = -1;
	}
}

void	close_all_fds(t_data *data)
{
	close_fd_set_minus1(&data->urandom);
	close_fd_set_minus1(&data->fd[0]);
	close_fd_set_minus1(&data->fd[1]);
	close_fd_set_minus1(&data->std_in);
	close_fd_set_minus1(&data->temp1_fd);
	close_fd_set_minus1(&data->temp2_fd);
}

void	reset_ints(t_data *data)
{
	data->pos = 0;
	data->text_len = -1;
	data->urandom = -1;
	data->index = -1;
	data->exec_num = -1;
	data->pid = -1;
	data->pipe_num = -1;
	data->has_quotes = -1;
}
