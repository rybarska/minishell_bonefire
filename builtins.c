/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 22:50:41 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/11 22:50:44 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_from_env(t_data *data, char *str_to_kill)
{
	int	i;

	i = 0;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		if (ft_strncmp(data->ft_environ[i], str_to_kill, ft_strlen(str_to_kill)) == 0
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
	if (var_to_kill[0] == NULL)
		boo(data, "unset: Not enough arguments\n", NULL, 2);
	while (var_to_kill[i] != NULL)
	{
		remove_from_env(data, var_to_kill[i]);
		i++;
	}
}

int	is_builtin(char *command)
{
	if (ft_strcmp(command, "cd") == 0
		|| ft_strcmp(command, "echo") == 0
		|| ft_strcmp(command, "env") == 0
		|| ft_strcmp(command, "exit") == 0
		|| ft_strcmp(command, "export") == 0
		|| ft_strcmp(command, "pwd") == 0
		|| ft_strcmp(command, "unset") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_data *data, t_exec **exec, char *command)
{
	char	**arguments;

	if (ft_strcmp(command, "cd") == 0)
		execute_cd(data, (*exec)->arguments[1]);
	else if (ft_strcmp(command, "echo") == 0)
		execute_echo(exec);
	else if (ft_strcmp(command, "env") == 0)
		execute_env(data);
	else if (ft_strcmp(command, "exit") == 0)
		execute_exit(data);
	else if (ft_strcmp(command, "export") == 0)
		execute_export(data, (*exec)->arguments);
	else if (ft_strcmp(command, "pwd") == 0)
		execute_pwd();
	else if (ft_strcmp(command, "unset") == 0)
	{
		arguments = (*exec)->arguments;
		execute_unset(data, arguments);
	}
	else
		return (1);
	return (0);
}
