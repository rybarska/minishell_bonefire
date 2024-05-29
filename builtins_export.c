/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 21:28:12 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/20 21:28:13 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_var_in_env(t_data *data, char *name)
{
	int	i;

	i = 0;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], name, ft_strlen(name)) == 0
			&& data->ft_environ[i][ft_strlen(name)] == '=')
			return (1);
		i++;
	}
	return (0);
}

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
		{
			duplicate_value = ft_strdup("");
			if (!duplicate_value)
				snuff_it(data, "Error duplicating string\n", NULL, 255);
		}
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
	final_value = get_or_duplicate_value(data, name, value);
	temp = ft_strdup(final_value);
	if (!temp)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	process_vars_and_quotes(data, &temp);
	if (is_var_in_env(data, name))
		update_var_in_env(data, name, temp);
	else
		add_var_to_env(data, name, temp);
	free(temp);
	if (final_value)
		free(final_value);
}

// This function looks for name and value of exported env var.
// It calls set_env_var, which leads to modification of data->ft_environ.
void	execute_export(t_data *data, char **args)
{
	int	i;
	char	*name_end;
	char	*name;
	char	*value;

	i = 1;
	if (!args[1])
		return (print_export_strings(data));
	while (args[i])
	{
		value = NULL;
		name_end = ft_strchr(args[i], '=');
		if (name_end)
		{
			*name_end = '\0';
			value = name_end + 1;
		}
		name = args[i];
		if (check_env_var_name(data, name) == 0)
		{
			set_env_var(data, name, value);
		}
		if (name_end)
			*name_end = '=';
		i++;
	}
}
