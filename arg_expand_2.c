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

int	add_expanded(char **temp_str, char *expanded)
{
	char	*expanded_dup;
	char	*temp;

	expanded_dup = NULL;
	temp = NULL;
	expanded_dup = ft_strdup(expanded);
	if (!expanded_dup)
		return (255);
	temp = ft_strjoin(*temp_str, expanded_dup);
	free(expanded_dup);
	free(*temp_str);
	if (!temp)
		return (255);
	*temp_str = temp;
	return (0);
}

// This function calls getenv and returns either the expanded var or NULL
int	allocate_and_expand(char **temp_str, char *var_name_start,
	char *var_name_end)
{
	char	*var_name;
	char	*expanded;

	expanded = NULL;
	var_name = (char *)malloc(sizeof(char)
			* (var_name_end - var_name_start + 1));
	if (!var_name)
		return (255);
	ft_strlcpy(var_name, var_name_start, var_name_end - var_name_start + 1);
	expanded = getenv(var_name); //write ft_getenv that gets it from ft_environ
	//move local allocs into struct & update snuff_it function
	free(var_name);
	if (expanded)
	{
		if (add_expanded(temp_str, expanded) == 255)
			return (255);
	}
	return (0);
}
