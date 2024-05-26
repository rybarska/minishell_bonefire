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

/*void	free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
			free(array[i]);
		free(array);
	}
}*/

void	reset_ints(t_data *data)
{
	data->pos = 0;
	data->text_len = -1;
	data->urandom = -1;
	data->index = -1;
	data->exec_num = -1;
	data->pipe_fd_num = -1;
	data->pid = -1;
	//data->last_exit_code = 0;
}

/*void	child_snuff_it(t_data *data, char *error_msg, char *name, int exit_code)
{
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_msg, ft_strlen(error_msg));
	clean_up_data(data);
	exit(exit_code);
}

void	child_exit_like_a_boss(t_data *data, int exit_code)
{
	clean_up_data(data);
	exit(exit_code);
}*/
