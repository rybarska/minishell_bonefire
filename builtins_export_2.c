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
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	new_var = ft_strjoin(temp_var, value);
	free(temp_var);
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
}

void	add_var_to_env(t_data *data, char *name, char *value)
{
	int	i;
	char	*temp_var;
	char	*new_var;
	char	**temp;

	i = 0;
	temp_var = ft_strjoin(name, "=");
	if (!temp_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	new_var = ft_strjoin(temp_var, value);
	free(temp_var);
	if (!new_var)
		snuff_it(data, "Error allocating memory\n", NULL, 255);
	while (data->ft_environ && data->ft_environ[i] != NULL)
		i++;
	temp = ft_str_arr_join(data->ft_environ, new_var);
	free(new_var);
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

void	check_env_var_name(t_data *data, char *name)
{
	(void) data;
	int	i;

	i = -1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		snuff_it(data, "( not a valid identifier)\n", name, 1);
	while (name[++i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			snuff_it(data, "( not a valid identifier)\n", name, 1);
	}
}
