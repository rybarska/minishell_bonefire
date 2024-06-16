/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:02:06 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/16 18:02:09 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_env_vars(t_data *data, char *old_dir)
{
	char	curr_dir[PATH_MAX];

	execute_export(data, (char *[]){"OLDPWD", old_dir, NULL});	
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

void	change_directory(t_data *data, char *dir)
{
	char	curr_dir[PATH_MAX];

	if (getcwd(curr_dir, sizeof(curr_dir)) == NULL)
	{
		perror("cd");
		data->last_exit_code = 1;
		return ;
	}
	if (chdir(dir))
	{
		perror("cd");
		data->last_exit_code = 1;
		return ;
	}
	update_env_vars(data, curr_dir);
}

void	execute_cd(t_data *data, char *dir)
{
	char	*home_dir;


	if (dir == NULL)
	{
		home_dir = ft_getenv(data, "HOME");
		if (home_dir == NULL)
		{
			boo(data, "cd: HOME not set\n", NULL, 1);
			return ;
		}
		dir = home_dir;
		data->last_exit_code = 0;
	}
	change_directory(data, dir);
}
