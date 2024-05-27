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

	if (dir == NULL)
	{
		home_dir = getenv("HOME");
		if (home_dir == NULL)
		{
			boo(data, "expected argument to \"cd\"\n", NULL, 2);
			return ;
		}
		dir = home_dir;
	}
	if (chdir(dir) != 0)
	{
		perror("cd");
		return ;
	}
	/*if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
		execute_export("PWD", curr_dir, 1) != 0)
	else
		boo("error in getcwd\n");*/ //TODO: fix this when export is ready
}

void	execute_echo(t_exec **exec)
{
	int	omit_newline;
	int	print_index;
	int	i;

	omit_newline = 0;
	if ((*exec)->arguments[1] != NULL && ft_strncmp((*exec)->arguments[1], "-n", 2) == 0)
		omit_newline = 1;
	if (omit_newline)
		print_index = 2;
	else
		print_index = 1;
	i = print_index;
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
	//clean_up_env_vars(data); //TODO: if clean_up_env_vars not called in cleanup
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
