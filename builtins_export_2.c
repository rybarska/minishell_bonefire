/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 23:34:15 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/24 23:34:17 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_var_in_env(t_data *data, char *name, char *value)
{
	int	i;
	char	*temp_var;
	char	*new_var;

	i = 0;
	temp_var = NULL;
	new_var = NULL;
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	new_var = ft_strjoin(temp_var, value);
	free(temp_var);
	temp_var = NULL;
	if (!new_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], name, ft_strlen(name)) == 0
			&& data->ft_environ[i][ft_strlen(name)] == '=')
		{
			free(data->ft_environ[i]);
			data->ft_environ[i] = new_var;
			return ;
		}
		i++;
	}
	free(new_var);
	new_var = NULL;
}

void	add_var_to_env(t_data *data, char *name, char *value)
{
	int	i;
	char	*temp_var;
	char	*new_var;
	char	**temp;

	i = 0;
	temp_var = NULL;
	new_var = NULL;
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	new_var = ft_strjoin(temp_var, value);
	free(temp_var);
	temp_var = NULL;
	if (!new_var)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	while (data->ft_environ && data->ft_environ[i] != NULL)
		i++;
	temp = ft_str_arr_join(data->ft_environ, new_var);
	if (!temp)
		snuff_it(data, "Error allocating in add_var_to_env\n", NULL, 255);
	free(new_var);
	new_var = NULL;
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

int	check_env_var_name(t_data *data, char *name)
{
	int	i;

	i = -1;
	if (!name || !name[0])
		return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	if (!ft_isalpha(name[0]) && name[0] != '_' && name[0] != '/')
		return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	while (name[++i])
	{
		if (!ft_isalnum_or_(name[i]) && name[0] != '/')
			return (boo(data, "(not a valid identifier)\n", name, 1), 1);
	}
	return (0);
}
