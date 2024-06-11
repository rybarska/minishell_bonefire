/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:45:09 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:19 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_all_cmd_paths(t_data *data)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	if (!data->ft_environ[i])
		return ;
	data->cmd_paths = ft_split(data->ft_environ[i] + 5, ':');
	if (!data->cmd_paths)
		snuff_it(data, "Error creating split paths\n", NULL, 255);
	i = -1;
	while (data->cmd_paths[++i])
	{
		temp = data->cmd_paths[i];
		data->cmd_paths[i] = ft_strjoin(data->cmd_paths[i], "/");
		free(temp);
		temp = NULL;
		if (data->cmd_paths[i] == NULL)
			snuff_it(data, "Error activating paths\n", NULL, 255);
	}
}

void	get_path_from_env(t_data *data, char *command)
{
	int	i;

	i = -1;
	if (data->cmd_paths != NULL)
	{
		while (data->cmd_paths[++i])
		{
			data->found_path = ft_strjoin(data->cmd_paths[i], command);
			if (!data->found_path)
				snuff_it(data, "Error allocating for found_path\n", NULL, 255);
			if (access(data->found_path, R_OK | X_OK) == 0)
				break ;
			else
			{
				free(data->found_path);
				data->found_path = NULL;
			}
		}
	}
}

void	check_if_full_path(t_data *data, t_exec **exec, char *command)
{
	char	*last_slash;

	last_slash = ft_strrchr(command, '/');
	if (last_slash)
	{
		if (ft_strchr(command, '$'))
			command = expand_arg(data, command);
		if (ft_strchr(command, '\'') || ft_strchr(command, '\"'))
			command = rm_quotes(data, command);
		if (access(command, R_OK | X_OK) == 0)
		{
			data->found_path = ft_strdup(command);
			if (!data->found_path)
				snuff_it(data, "Error duplicating string\n", NULL, 255);
			(*exec)->is_full_path = 1;
		}
	}
}
