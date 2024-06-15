/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:33:00 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*make_empty_exec(t_data *data)
{
	t_exec	*exec;

	exec = NULL;
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		snuff_it(data, "Error allocating memory for exec\n", NULL, 255);
	exec->name = NULL;
	exec->cmd_exec_path = NULL;
	exec->is_full_path = 0;
	exec->in_redirs = NULL;
	exec->out_redirs = NULL;
	exec->arguments = NULL;
	exec->next = NULL;
	exec->previous = NULL;
	exec->is_export = 0;
	return (exec);
}

void	exec_lstadd_back(t_exec **lst, t_exec *new)
{
	t_exec	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

int	count_executives(t_data *data)
{
	int		exec_counter;
	t_exec	*current;

	exec_counter = 0;
	current = data->exec_list_head;
	while (current != NULL)
	{
		exec_counter++;
		current = current->next;
	}
	data->exec_num = exec_counter;
	return (exec_counter);
}
