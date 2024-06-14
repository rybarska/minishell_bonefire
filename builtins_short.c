/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_short.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:50:57 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:25:13 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(t_data *data, char *dir)
{
	char	*home_dir;
	char	curr_dir[PATH_MAX];

	if (dir == NULL)
	{
		home_dir = ft_getenv(data, "HOME");
		if (home_dir == NULL)
		{
			boo(data, "expected argument to \"cd\"\n", NULL, 1);
			return ;
		}
		dir = home_dir;
		data->last_exit_code = 0;
	}
	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		execute_export(data, (char *[]){"PWD", curr_dir, NULL});
		data->last_exit_code = 0;
	}
	else
	{
		perror("cd");
		data->last_exit_code = 1;
	}
}

void	execute_echo(t_exec **exec)
{
	int	omit_newline;
	int	i;
	int	j;

	omit_newline = 0;
	i = 0;
	while ((*exec)->arguments[++i]
		&& ft_strncmp((*exec)->arguments[i], "-n", 2) == 0)
	{
		j = 2;
		while ((*exec)->arguments[i][j] == 'n')
			j++;
		if ((*exec)->arguments[i][j] != '\0')
			break ;
		omit_newline = 1;
	}
	while ((*exec)->arguments[i])
	{
		printf("%s", (*exec)->arguments[i]);
		if ((*exec)->arguments[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (!omit_newline)
		printf("\n");
}

void	execute_env(t_data *data, char **args)
{
	int	i;

	i = 0;
	if (args && args[1])
	{
		boo(data, "No such file or directory\n", args[1], 127);
		return ;
	}
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		printf("%s\n", data->ft_environ[i]);
		i++;
	}
	data->last_exit_code = 0;
}

void	execute_exit(t_data *data, char **args)
{
	if (args && args[1])
		data->last_exit_code = ft_atoi(args[1]);
	exit_like_a_boss(data, data->last_exit_code);
}

void	execute_pwd(t_data *data)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		printf("%s\n", curr_dir);
		data->last_exit_code = 0;
	}
	else
	{
		perror("pwd");
		boo(data, NULL, NULL, 1);
	}
}
