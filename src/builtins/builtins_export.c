/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:12 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/21 13:03:54 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value_from_list(t_data *data, char *name)
{
	t_env_var	*current_var;
	char		*found_value;

	found_value = NULL;
	current_var = data->env_vars_head;
	while (current_var)
	{
		if (current_var->name && ft_strcmp(current_var->name, name) == 0)
		{
			if (current_var->value)
			{
				found_value = ft_strdup(current_var->value);
				if (!found_value)
					snuff_it(data, "Error duplicating string\n", NULL, 255);
			}
			break ;
		}
		current_var = current_var->next;
	}
	return (found_value);
}

char	*get_or_duplicate_value(t_data *data, char *name, char *value)
{
	char	*duplicate_value;

	if (!value)
	{
		duplicate_value = get_value_from_list(data, name);
		if (!duplicate_value)
			return (NULL);
	}
	else
	{
		duplicate_value = ft_strdup(value);
		if (!duplicate_value)
			snuff_it(data, "Error duplicating string\n", NULL, 255);
	}
	return (duplicate_value);
}

static void	set_env_var(t_data *data, char *name, char *value)
{
	char	*temp;
	char	*final_value;

	temp = NULL;
	if (ft_strcmp(name, "PATH") == 0)
		free_hashtable(data->hashtab, false);
	final_value = get_or_duplicate_value(data, name, value);
	if (!final_value)
		return ;
	add_string_to_thrash_list(data, final_value);
	temp = ft_strdup(final_value);
	if (!temp)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	add_string_to_thrash_list(data, temp);
	if (is_var_in_env(data, name))
		update_var_in_env(data, name, temp);
	else
		add_var_to_env(data, name, temp);
}

void	separate_name_and_value(t_data *data, char **value_to_pass,
	char **name_end, char **value)
{
	*value_to_pass = ft_strdup(*name_end);
	if (!*value_to_pass)
		snuff_it(data, "Error duplicating string\n", NULL, 255);
	add_string_to_thrash_list(data, *value_to_pass);
	**name_end = '\0';
	*value = *name_end + 1;
}

// This function looks for name and value of exported env var.
// It calls set_env_var, which leads to modification of data->ft_environ.
void	execute_export(t_data *data, char **args)
{
	int		i;
	char	*name_end;
	char	*name;
	char	*value;
	char	*value_to_pass;

	if (!args[1])
		return (print_export_strings(data));
	i = 0;
	while (args[++i])
	{
		value = NULL;
		value_to_pass = NULL;
		name_end = ft_strchr(args[i], '=');
		if (name_end)
			separate_name_and_value(data, &value_to_pass, &name_end, &value);
		name = args[i];
		if (check_env_var_name(data, name, value_to_pass) == 0)
		{
			set_env_var(data, name, value);
			data->last_exit_code = 0;
		}
		if (name_end)
			*name_end = '=';
	}
}
