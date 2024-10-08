/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_lone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:44:11 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:32 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_lone_external(t_data *data, t_exec **exec)
{
	data->pid = fork();
	if (data->pid < 0)
		snuff_it(data, "Error forking\n", NULL, 255);
	if (data->pid == 0)
	{
		set_mode(data, CHILD);
		close_fd_set_minus1(&data->temp1_fd);
		close_fd_set_minus1(&data->temp2_fd);
		if (!(*exec)->cmd_exec_path || !(*exec)->arguments[0]
			|| !(*exec)->arguments[0][0])
			snuff_it(data, "Error: command not found\n", (*exec)->arguments[0],
				127);
		if (execve((*exec)->cmd_exec_path, (*exec)->arguments,
				data->ft_environ) == -1)
			snuff_it(data, "Is a directory or error executing command\n",
				(*exec)->arguments[0], 126);
	}
	else
		handle_parent(data, exec);
}

static void	execute_lone_builtin(t_data *data, t_exec **exec)
{
	if ((*exec)->arguments && ft_strcmp((*exec)->arguments[0], "exit") == 0
		&& (!(*exec)->arguments[1] || !(*exec)->arguments[2]))
	{
		close_fd_set_minus1(&data->temp1_fd);
		close_fd_set_minus1(&data->temp2_fd);
	}
	if (execute_builtin(data, exec, (*exec)->arguments[0]) != 0)
		snuff_it(data, "Error: command not found\n", (*exec)->arguments[0],
			127);
}

static void	restore_stds(t_data *data, t_exec **exec)
{
	if (dup2(data->temp1_fd, STDIN_FILENO) < 0)
	{
		close_fd_set_minus1(&data->temp1_fd);
		snuff_it(data, "Error redirecting temp fd\n", (*exec)->name, 255);
	}
	if (dup2(data->temp2_fd, STDOUT_FILENO) < 0)
	{
		close_fd_set_minus1(&data->temp2_fd);
		snuff_it(data, "Error redirecting temp fd\n", (*exec)->name, 255);
	}
}

void	execute_lone_exec_no_pipe(t_data *data, t_exec **exec)
{
	data->temp1_fd = dup(STDIN_FILENO);
	if (data->temp1_fd < 0)
		snuff_it(data, "Error duplicating STDIN_FILENO\n", NULL, 255);
	data->temp2_fd = dup(STDOUT_FILENO);
	if (data->temp2_fd < 0)
	{
		close_fd_set_minus1(&data->temp1_fd);
		snuff_it(data, "Error duplicating STDOUT_FILENO\n", NULL, 255);
	}
	if (process_in_files(data, exec) > 0 || process_out_files(data, exec) > 0)
	{
		restore_stds(data, exec);
		return ;
	}
	if ((*exec)->arguments && is_builtin((*exec)->arguments[0]))
		execute_lone_builtin(data, exec);
	else if ((*exec)->arguments)
	{
		execute_lone_external(data, exec);
		wait_for_children(data);
	}
	restore_stds(data, exec);
}
