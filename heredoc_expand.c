/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:16:14 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:05 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_add_expanded(t_data *data, char **temp_str, char *expanded)
{
	char	*expanded_dup;
	char	*temp;

	expanded_dup = NULL;
	temp = NULL;
	expanded_dup = ft_strdup(expanded);
	if (!expanded_dup)
		snuff_it(data, "Error allocating in heredoc_add_expanded", NULL, 255);
	add_string_to_thrash_list(data, expanded_dup);
	temp = ft_strjoin(*temp_str, expanded_dup);
	//free(expanded_dup);
	//expanded_dup = NULL;
	free(*temp_str);
	if (!temp)
		snuff_it(data, "Error allocating in heredoc_add_expanded", NULL, 255);
	*temp_str = temp;
}

// This function calls ft_getenv and returns either the expanded var or NULL
static void	heredoc_allocate_and_expand(t_data *data, char **temp_str,
		char *var_name_start, char *var_name_end)
{
	char	*var_name;
	char	*expanded;

	expanded = NULL;
	var_name = NULL;
	var_name = (char *)malloc(sizeof(char) * (var_name_end - var_name_start
				+ 1));
	if (!var_name)
		snuff_it(data, "Error allocating in allocate_and_expand", NULL, 255);
	add_string_to_thrash_list(data, var_name);
	ft_strlcpy(var_name, var_name_start, var_name_end - var_name_start + 1);
	expanded = ft_getenv(data, var_name);
	// free(var_name);
	// var_name = NULL;
	if (expanded)
		heredoc_add_expanded(data, temp_str, expanded);
}

// This function calls allocate_and_expand if it finds a variable name
// and otherwise returns NULL.
// It also keeps track of flags for single or double quotes.
static void	expand_name(t_data *data, char **var_value, char **temp_str)
{
	char *var_name_start;
	char *var_name_end;

	(*var_value)++;
	var_name_start = *var_value;
	var_name_end = var_name_start;
	while (*var_name_end && ft_isalnum_or_(*var_name_end))
	{
		if (*var_name_end == '\'' && !data->is_d_quoted)
			data->is_s_quoted = !data->is_s_quoted;
		if (*var_name_end == '\"' && !data->is_s_quoted)
			data->is_d_quoted = !data->is_d_quoted;
		var_name_end++;
		(*var_value)++;
	}
	if (var_name_end != var_name_start)
		heredoc_allocate_and_expand(data, temp_str, var_name_start,
				var_name_end);
}

static char	*add_one_char(t_data *data, char **arg, char *temp_str)
{
	char	*temp;

	temp = NULL;
	if (**arg == '\'' && !data->is_d_quoted)
		data->is_s_quoted = !data->is_s_quoted;
	if (**arg == '\"' && !data->is_s_quoted)
		data->is_d_quoted = !data->is_d_quoted;
	temp = ft_strjoin_char(temp_str, **arg);
	if (!temp)
		snuff_it(data, "Error allocating in add_one_char\n", NULL, 255);
	free(temp_str);
	temp_str = NULL;
	temp_str = temp;
	(*arg)++;
	return (temp_str);
}

// This function sets flags for single or double quotes.
// It calls expand_name if it finds a variable outside quotes
// or inside double quotes.
// Otherwise it just adds characters one by one to temp_str.
char	*heredoc_expand_var(t_data *data, char *arg)
{
	char	*temp_str;

	data->is_s_quoted = 0;
	data->is_d_quoted = 0;
	temp_str = ft_strdup("");
	if (!temp_str)
		snuff_it(data, "Error allocating memory for temp_str\n", NULL, 255);
	while (*arg)
	{
		if (*arg == '$')
			expand_name(data, &arg, &temp_str);
		else
			temp_str = add_one_char(data, &arg, temp_str);
	}
	return (temp_str);
}
