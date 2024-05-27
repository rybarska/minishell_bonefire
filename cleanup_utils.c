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
			perror("Error closing file descriptor\n");
		*fd = -1;
	}
}

void	reset_ints(t_data *data)
{
	data->pos = 0;
	data->text_len = -1;
	data->urandom = -1;
	data->index = -1;
	data->exec_num = -1;
	data->pid = -1;
}
