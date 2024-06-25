/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:50:41 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/25 19:42:31 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_env(t_data *data, char *str_to_kill)
{
	int	i;

	i = 0;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], str_to_kill,
				ft_strlen(str_to_kill)) == 0
			&& data->ft_environ[i][ft_strlen(str_to_kill)] == '=')
		{
			free(data->ft_environ[i]);
			while (data->ft_environ && data->ft_environ[i + 1] != NULL)
			{
				data->ft_environ[i] = data->ft_environ[i + 1];
				i++;
			}
			data->ft_environ[i] = NULL;
			break ;
		}
		i++;
	}
}

static void	execute_unset(t_data *data, char **var_to_kill)
{
	int	i;

	i = 0;
	if (var_to_kill[1] == NULL)
		return (boo(data, "unset: Not enough arguments\n", NULL, 1));
	while (var_to_kill[i] != NULL)
	{
		if (ft_strcmp(var_to_kill[i], "PATH") == 0)
			free_hashtable(data->hashtab, false);
		remove_from_env(data, var_to_kill[i]);
		i++;
	}
	data->last_exit_code = 0;
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0 || ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "env") == 0 || ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "export") == 0 || ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "unset") == 0 || ft_strcmp(command, "hash") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_data *data, t_exec **exec, char *command)
{
	char	**arguments;

	if (ft_strcmp(command, "cd") == 0)
		execute_cd(data, (*exec)->arguments[1]);
	else if (ft_strcmp(command, "echo") == 0)
	{
		execute_echo(exec);
		data->last_exit_code = 0;
	}
	else if (ft_strcmp(command, "env") == 0)
		execute_env(data, (*exec)->arguments);
	else if (ft_strcmp(command, "exit") == 0)
		execute_exit(data, (*exec)->arguments);
	else if (ft_strcmp(command, "export") == 0)
		execute_export(data, (*exec)->arguments);
	else if (ft_strcmp(command, "pwd") == 0)
		execute_pwd(data);
	else if (ft_strcmp(command, "unset") == 0)
	{
		arguments = (*exec)->arguments;
		execute_unset(data, arguments);
	}
	else if (ft_strcmp(command, "hash") == 0)
		execute_hash(data);
	return (0);
}
