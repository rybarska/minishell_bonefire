/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:34:15 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:06 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_var_in_env(t_data *data, char *name)
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

void	update_var_in_env(t_data *data, char *name, char *value)
{
	int		i;
	char	*temp_var;
	char	*new_var;

	i = -1;
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	add_string_to_thrash_list(data, temp_var);
	new_var = ft_strjoin(temp_var, value);
	if (!new_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	while (data->ft_environ && data->ft_environ[++i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], name, ft_strlen(name)) == 0
			&& data->ft_environ[i][ft_strlen(name)] == '=')
		{
			free(data->ft_environ[i]);
			data->ft_environ[i] = new_var;
			return ;
		}
	}
	free(new_var);
	new_var = NULL;
}

void	add_var_to_env(t_data *data, char *name, char *value)
{
	int		i;
	char	*temp_var;
	char	*new_var;
	char	**temp;

	i = 0;
	temp_var = NULL;
	new_var = NULL;
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	add_string_to_thrash_list(data, temp_var);
	new_var = ft_strjoin(temp_var, value);
	if (!new_var)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	add_string_to_thrash_list(data, new_var);
	while (data->ft_environ && data->ft_environ[i] != NULL)
		i++;
	temp = ft_str_arr_join(data->ft_environ, new_var);
	if (!temp)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	ft_free_array(data->ft_environ);
	data->ft_environ = temp;
}

void	print_export_strings(t_data *data)
{
	int	i;

	i = 0;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		printf("export %s\n", data->ft_environ[i]);
		i++;
	}
}

int	check_env_var_name(t_data *data, char *name, char *value)
{
	int	i;

	i = -1;
	(void)value;
	if (!name || !name[0])
		return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	while (name[++i])
	{
		if (!ft_isalnum_or_(name[i]))
			return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	}
	return (0);
}
