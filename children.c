/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 19:43:33 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/29 19:43:35 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_parent(t_data *data, t_exec **exec)
{
	(void) *exec;
	t_process	*new_process;

	new_process = (t_process *)malloc(sizeof(t_process));
	if (!new_process)
		snuff_it(data, "Error allocating memory for new process\n", NULL, 255);
	new_process->child_pid = data->pid;
	new_process->status = -1;
	new_process->next = NULL;
	if (!data->child_list_tail)
	{
		data->child_list_head = new_process;
		data->child_list_tail = new_process;
	}
	else
	{
		data->child_list_tail->next = new_process;
		data->child_list_tail = data->child_list_tail->next;
	}
}

static void	make_child(t_data *data, t_exec **exec)
{
	if (pipe(data->fd) < 0)
		snuff_it(data, "Error creating pipe fds\n", (*exec)->name, 255);
	data->pid = fork();
	if (data->pid < 0)
		snuff_it(data, "Error forking\n", NULL, 255);
	if (data->pid == 0)
	{
		//printf("data->fd[0]: %d\n", data->fd[0]);
		//printf("data->fd[1]: %d\n", data->fd[1]);
		//printf("*data->std_in: %d\n", *data->std_in);
		//dprintf(2, "EXEC NUM: %d, INDEX: %d\n", data->exec_num, data->index);
		if (data->index == 0)
			exec_first_command(data, *exec);
		else if (data->index == data->exec_num - 1)
			exec_last_command(data, *exec);
		else
			exec_mid_command(data, *exec);
	}
	else
		handle_parent(data, exec);
	close_fd_set_minus1(&data->std_in);
	data->std_in = dup(data->fd[0]);
	if (data->std_in < 0)
		snuff_it(data, "Error duplicating pipe fd\n", (*exec)->name, 255);
	close_fd_set_minus1(&data->fd[0]);
	close_fd_set_minus1(&data->fd[1]);
}

void	execute_execs(t_data *data)
{
	t_exec	*curr_exec;

	if (data->exec_num == 0)
		return ;
	data->std_in = dup(STDIN_FILENO);
	if (data->std_in < 0)
		snuff_it(data, "Error duplicating STDIN_FILENO\n", NULL, 255);
	curr_exec = data->exec_list_head;
	while (curr_exec)
	{
		++(data->index);
		if (data->exec_num == 1)
		{
			close_fd_set_minus1(&data->std_in);
			execute_lone_exec_no_pipe(data, &curr_exec);
		}
		else
			make_child(data, &curr_exec);
		curr_exec = curr_exec->next;
	}
	close_fd_set_minus1(&data->std_in);
}
