/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 19:42:42 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/26 19:42:45 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_expanded(t_data *data, char **temp_str, char *expanded)
{
	char	*expanded_dup;
	char	*temp;

	expanded_dup = NULL;
	temp = NULL;
	expanded_dup = ft_strdup(expanded);
	if (!expanded_dup)
		snuff_it(data, "Error allocating in add_expanded", NULL, 255);
	temp = ft_strjoin(*temp_str, expanded_dup);
	free(expanded_dup);
	expanded_dup = NULL;
	free(*temp_str);
	if (!temp)
		snuff_it(data, "Error allocating in add_expanded", NULL, 255);
	*temp_str = temp;
}

// This function calls ft_getenv and returns either the expanded var or NULL
void	allocate_and_expand(t_data *data, char **temp_str, char *var_name_start,
	char *var_name_end)
{
	char	*var_name;
	char	*expanded;

	expanded = NULL;
	var_name = NULL;
	var_name = (char *)malloc(sizeof(char)
			* (var_name_end - var_name_start + 1));
	if (!var_name)
		snuff_it(data, "Error allocating in allocate_and_expand", NULL, 255);
	ft_strlcpy(var_name, var_name_start, var_name_end - var_name_start + 1);
	expanded = ft_getenv(data, var_name); //write ft_getenv that gets it from ft_environ
	//IF: not there, THEN: look locals
	//move local allocs into struct & update snuff_it function
	free(var_name);
	var_name = NULL;
	if (expanded)
		add_expanded(data, temp_str, expanded);
}
