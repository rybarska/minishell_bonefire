/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:03:26 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/12 22:24:19 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmd_array(t_data *data, t_token_node *node, int arg_count,
		t_exec *exec)
{
	t_token_node	*current;
	int				i;
	char			*temp;

	current = node;
	temp = NULL;
	exec->arguments = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!exec->arguments)
		snuff_it(data, "Error allocating memory for exec args\n", NULL, 255);
	i = 0;
	while (i < arg_count && current != NULL && current->value != NULL)
	{
		if (is_substantive(current->type) || current->type == EXPORT)
		{
			temp = ft_strdup(current->value);
			if (!temp)
				snuff_it(data, "Error allocating memory\n", NULL, 255);
			process_vars_and_quotes(data, &temp);
			exec->arguments[i] = temp;
			i++;
		}
		current = current->next;
	}
	exec->arguments[i] = NULL;
}

void	look_for_path(t_data *data, t_exec **exec, char *command)
{
	(*exec)->cmd_exec_path = hash_lookup(data->hashtab, command);
	if ((*exec)->cmd_exec_path)
		return ;
	check_if_full_path(data, exec, command);
	if (!(*exec)->is_full_path && data->cmd_paths != NULL)
		get_path_from_env(data, command);
	if (data->found_path)
	{
		(*exec)->cmd_exec_path = ft_strdup(data->found_path);
		if (!(*exec)->cmd_exec_path)
			snuff_it(data, "Error allocating for exec\n", NULL, 255);
		if (!store_data(data->hashtab, command, data->found_path))
			snuff_it(data, "Error in hashtable storage\n", NULL, 255);
		free(data->found_path);
		data->found_path = NULL;
	}
}

void	put_cmd_in_exec(t_data *data, t_token_node *node, int arg_count,
		t_exec **exec)
{
	char	*temp;

	temp = NULL;
	if (data->found_path)
	{
		free(data->found_path);
		data->found_path = NULL;
	}
	if (node && node->value && (is_substantive(node->type)
			|| node->type == EXPORT))
	{
		temp = ft_strdup(node->value);
		if (!temp)
			snuff_it(data, "Error duplicating string\n", NULL, 255);
		process_vars_and_quotes(data, &temp);
		(*exec)->name = temp;
		if (is_builtin(temp))
			(*exec)->cmd_exec_path = NULL;
		else
			look_for_path(data, exec, temp);
		make_cmd_array(data, node, arg_count, *exec);
	}
}
