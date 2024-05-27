/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_commands.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:03:26 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/18 20:03:28 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_cmd_array(t_data *data, t_token_node *node, int arg_count,
	t_exec *exec)
{
	t_token_node	*current;
	int				i;
	char		*temp;

	current = node;
	temp = NULL;
	exec->arguments = (char **)malloc((arg_count + 1) * sizeof(char *));
	if (!exec->arguments)
		snuff_it(data, "Error allocating memory for exec args\n", NULL, 255);
	i = 0;
	while (i < arg_count && current != NULL)
	{
		temp = ft_strdup(current->value);
		if (!temp)
			snuff_it(data, "Error allocating memory\n", NULL, 255);
		if (!exec->is_export)
			process_vars_and_quotes(data, &temp);
		exec->arguments[i] = temp;
		//printf("exec->arguments[%d]: %s\n", i, exec->arguments[i]);
		current = current->next;
		i++;
	}
	exec->arguments[i] = NULL;
}

void	look_for_path(t_data *data, t_exec **exec, char	*command)
{
	//check if hashed
	check_if_full_path(data, exec, command);
	if (!(*exec)->is_full_path && data->cmd_paths != NULL)
		get_path_from_env(data, command);
	if (data->found_path)
	{
		(*exec)->cmd_exec_path = ft_strdup(data->found_path);
		if (!(*exec)->cmd_exec_path)
			snuff_it(data, "Error allocating for exec\n", NULL, 255);
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
	if (node && node->value)
	{
		temp = ft_strdup(node->value);
		if (!temp)
			snuff_it(data, "Error duplicating string\n", NULL, 255);
		if (!(*exec)->is_export)
			process_vars_and_quotes(data, &temp);
		(*exec)->name = temp;
		if (is_builtin(temp))
			(*exec)->cmd_exec_path = NULL;
		else
			look_for_path(data, exec, temp);
		make_cmd_array(data, node, arg_count, *exec);
	}
}
