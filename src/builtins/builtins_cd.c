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
	char	*res;

	res = ft_strjoin("OLDPWD=", old_dir);
	if (!res)
		snuff_it(data, "Error allocating for dir name\n", NULL, 255);
	add_string_to_thrash_list(data, res);
	execute_export(data, (char *[]){"export", res, NULL});
	if (getcwd(curr_dir, sizeof(curr_dir)) != NULL)
	{
		res = ft_strjoin("PWD=", curr_dir);
		if (!res)
			snuff_it(data, "Error allocating for dir name\n", NULL, 255);
		add_string_to_thrash_list(data, res);
		execute_export(data, (char *[]){"export", res, NULL});
		data->last_exit_code = 0;
	}
	else
	{
		perror("cd");
		data->last_exit_code = 1;
	}
}

int	are_args_too_many(t_data *data, char **args)
{
	if (args && args[1] && args[1][0] && args[2])
	{
		boo(data, "too many arguments\n", "cd", 1);
		data->last_exit_code = 1;
		return (1);
	}
	return (0);
}

void	execute_cd(t_data *data, char **args)
{
	char	*home_dir;

	if (are_args_too_many(data, args))
		return ;
	if (args[1] == NULL || ft_strcmp(args[1], "") == 0
		|| ft_strcmp(args[1], "HOME") == 0)
	{
		home_dir = ft_getenv(data, "HOME");
		if (home_dir == NULL)
		{
			boo(data, "cd: HOME not set\n", NULL, 1);
			data->last_exit_code = 1;
			return ;
		}
		args[1] = home_dir;
		data->last_exit_code = 0;
	}
	if (chdir(args[1]) == -1)
	{
		perror("cd");
		data->last_exit_code = 1;
		return ;
	}
	update_env_vars(data, args[1]);
}
