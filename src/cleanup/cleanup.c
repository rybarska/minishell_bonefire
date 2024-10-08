/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:45:15 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/03 15:51:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_up_env_vars(t_data *data)
{
	t_env_var	*current;
	t_env_var	*next;

	current = data->env_vars_head;
	while (current)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		current->name = NULL;
		if (current->value)
			free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	data->env_vars_head = NULL;
	if (data->ft_environ != NULL)
		ft_free_array(data->ft_environ);
	data->ft_environ = NULL;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
}

void	clean_up_data(t_data *data)
{
	if (data->exec_list_head != NULL)
		exec_lstclear(&data->exec_list_head);
	data->exec_list_head = NULL;
	if (data->token_list_head != NULL)
		token_node_lstclear(&data->token_list_head);
	data->token_list_tail = NULL;
	if (data->text)
		free(data->text);
	data->text = NULL;
	if (data->cmd_paths != NULL)
		ft_free_array(data->cmd_paths);
	data->cmd_paths = NULL;
	if (data->found_path)
		free(data->found_path);
	data->found_path = NULL;
	if (data->child_list_head)
		process_lstclear(&(data->child_list_head));
	data->child_list_head = NULL;
	data->child_list_tail = NULL;
	close_all_fds(data);
	if (data->thrash_list_head)
		clear_thrash_list(data);
	data->thrash_list_head = NULL;
	reset_ints(data);
}

void	snuff_it(t_data *data, char *error_msg, char *name, int exit_code)
{
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_msg, ft_strlen(error_msg));
	clean_up_data(data);
	clean_up_env_vars(data);
	free_hashtable(data->hashtab, true);
	exit(exit_code);
}

void	exit_like_a_boss(t_data *data, int exit_code)
{
	clean_up_data(data);
	clean_up_env_vars(data);
	free_hashtable(data->hashtab, true);
	exit(exit_code);
}
