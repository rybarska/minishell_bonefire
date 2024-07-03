/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:02:06 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/02 20:02:57 by mhuszar          ###   ########.fr       */
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
	char	*curr_to_old_dir;

	if (are_args_too_many(data, args))
		return ;
	curr_to_old_dir = ft_getenv(data, "PWD");
	if (args[1] == NULL || ft_strcmp(args[1], "") == 0
		|| ft_strcmp(args[1], "HOME") == 0)
	{
		home_dir = ft_getenv(data, "HOME");
		if (!home_dir || chdir(home_dir) == -1)
			return (boo(data, "cd: HOME not set\n", NULL, 1));
		update_env_vars(data, curr_to_old_dir);
		data->last_exit_code = 0;
	}
	else if (chdir(args[1]) == -1)
	{
		perror("cd");
		data->last_exit_code = 1;
		return ;
	}
	else
		update_env_vars(data, curr_to_old_dir);
}
