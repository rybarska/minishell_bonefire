/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_env_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:03:45 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:16 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_env_var_in_list(t_data *data, char *name, char *value,
		int is_exported)
{
	t_env_var	*current;

	if (!name || name[0] == '\0')
		return (boo(data, "Invalid env var name\n", NULL, 2), 0);
	current = data->env_vars_head;
	while (current != NULL)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (value)
			{
				if (current->value)
					free(current->value);
				current->value = ft_strdup(value);
			}
			current->is_exported = is_exported;
			return (1);
		}
		current = current->next;
	}
	return (0);
}

void	add_env_var_to_list(t_data *data, t_env_var *new_env_var)
{
	t_env_var	*current;

	if (data->env_vars_head == NULL)
		data->env_vars_head = new_env_var;
	else
	{
		current = data->env_vars_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_env_var;
	}
}

void	add_or_update_env_var_list(t_data *data, char *name, char *value,
		int is_exported)
{
	t_env_var	*new_env_var;

	if (update_env_var_in_list(data, name, value, is_exported))
		return ;
	new_env_var = (t_env_var *)malloc(sizeof(t_env_var));
	if (!new_env_var)
		snuff_it(data, "Error allocating for env var\n", NULL, 255);
	new_env_var->name = ft_strdup(name);
	if (!new_env_var->name)
		snuff_it(data, "Error duplicating string\n", NULL, 255);
	new_env_var->value = NULL;
	if (value)
	{
		new_env_var->value = ft_strdup(value);
		if (!new_env_var->value)
			snuff_it(data, "Error duplicating string\n", NULL, 255);
	}
	new_env_var->is_exported = is_exported;
	new_env_var->next = NULL;
	add_env_var_to_list(data, new_env_var);
}

void	put_env_in_list(t_data *data, t_token_node *node, int env_count,
		int is_exported)
{
	char	*name_end;
	char	*temp;

	temp = NULL;
	name_end = NULL;
	while (env_count-- > 0 && node && node->value)
	{
		temp = ft_strdup(node->value);
		if (!temp)
			snuff_it(data, "Error duplicating string\n", NULL, 255);
		name_end = ft_strchr(temp, '=');
		if (name_end)
		{
			*name_end = '\0';
			add_or_update_env_var_list(data, temp, name_end + 1, is_exported);
		}
		else
			add_or_update_env_var_list(data, temp, NULL, is_exported);
		free(temp);
		temp = NULL;
		node = node->next;
	}
}
