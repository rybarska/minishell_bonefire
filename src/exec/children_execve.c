/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_execve.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:44:46 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/19 21:23:27 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_external_or_builtin(t_data *data, t_exec *exec)
{
	if (process_in_files(data, &exec) || process_out_files(data, &exec))
		snuff_it(data, NULL, NULL, 1);
	if (!exec->arguments)
		exit_like_a_boss(data, data->last_exit_code);
	if (is_builtin(exec->arguments[0]))
	{
		if (execute_builtin(data, &exec, exec->arguments[0]) != 0)
			snuff_it(data, "Error: command not found\n", exec->arguments[0],
				127);
		exit_like_a_boss(data, data->last_exit_code);
	}
	if (!exec->cmd_exec_path || !exec->arguments[0] || !exec->arguments[0][0])
		snuff_it(data, "Error: command not found\n", exec->arguments[0], 127);
	if (execve(exec->cmd_exec_path, exec->arguments, data->ft_environ) == -1)
		snuff_it(data, "Is a directory or error executing command\n",
			exec->arguments[0], 126);
}

void	exec_last_command(t_data *data, t_exec *exec)
{
	close_fd_set_minus1(&data->fd[0]);
	if (dup2(data->std_in, STDIN_FILENO) < 0)
		snuff_it(data, "Error redirecting to STDIN_FILENO\n", exec->name, 255);
	close_fd_set_minus1(&data->std_in);
	close_fd_set_minus1(&data->fd[1]);
	execute_external_or_builtin(data, exec);
}

void	exec_mid_command(t_data *data, t_exec *exec)
{
	if (dup2(data->std_in, STDIN_FILENO) < 0)
		snuff_it(data, "Error redirecting to STDIN_FILENO\n", exec->name, 255);
	close_fd_set_minus1(&data->std_in);
	if (dup2(data->fd[1], STDOUT_FILENO) < 0)
		snuff_it(data, "Error redirecting pipe[1]\n", exec->name, 255);
	close_fd_set_minus1(&data->fd[1]);
	close_fd_set_minus1(&data->fd[0]);
	execute_external_or_builtin(data, exec);
}

void	exec_first_command(t_data *data, t_exec *exec)
{
	close_fd_set_minus1(&data->fd[0]);
	close_fd_set_minus1(&data->std_in);
	if (dup2(data->fd[1], STDOUT_FILENO) < 0)
		snuff_it(data, "Error redirecting pipe[1]\n", exec->name, 255);
	close_fd_set_minus1(&data->fd[1]);
	execute_external_or_builtin(data, exec);
}
