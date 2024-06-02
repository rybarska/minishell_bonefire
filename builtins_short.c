/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_short.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:50:57 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/16 22:51:00 by arybarsk         ###   ########.fr       */
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
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		return ;
	}
	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
		execute_export(data, (char *[]){"PWD", curr_dir, NULL});
	else
		perror("cd");
}

void	execute_echo(t_exec **exec)
{
	int	omit_newline;
	int	i;
	int	j;

	omit_newline = 0;
	i = 0;
	while ((*exec)->arguments[++i] != NULL
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

void	execute_env(t_data *data)
{
	int	i;

	i = 0;
	while (data->ft_environ && data->ft_environ[i] != NULL)
	{
		printf("%s\n", data->ft_environ[i]);
		i++;
	}
}

void	execute_exit(t_data *data)
{
	exit_like_a_boss(data, data->last_exit_code);
}

void	execute_pwd()
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
		printf("%s\n", curr_dir);
	else
		perror("minishell");
}
