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
	if (args && args[1][0] && args[2])
	{
		boo(data, "too many arguments\n", "exit", 1);
		data->last_exit_code = 1;
		return ;
	}
	else if (args && args[1])
	{
		data->last_exit_code = get_input_num(args[1]);
		if (data->last_exit_code == -264)
			boo(data, "numeric argument required\n", args[1], 2);
		else if (data->last_exit_code < 0 || data->last_exit_code > 255)
			boo(data, "Number outside range (0 to 255)\n", args[1], 69);
	}
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
