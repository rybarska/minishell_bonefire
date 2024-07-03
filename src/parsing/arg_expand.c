/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/03 21:42:40 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function calls allocate_and_expand if it finds a variable name
// and otherwise returns NULL.
// It also keeps track of flags for single or double quotes.
static void	expand_name(t_data *data, char **var_value, char **temp_str)
{
	char	*var_name_start;
	char	*var_name_end;

	(*var_value)++;
	if (!ft_isalpha(**var_value) && **var_value != '_')
	{
		(*var_value)++;
		return ;
	}
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
		allocate_and_expand(data, temp_str, var_name_start, var_name_end);
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

static void	get_exit_status(t_data *data, char **temp_str, char **arg)
{
	char	*exit_status_str;

	(*arg) += 2;
	exit_status_str = NULL;
	exit_status_str = ft_itoa(data->last_exit_code);
	if (!exit_status_str)
	{
		free(*temp_str);
		temp_str = NULL;
		snuff_it(data, "Error allocating memory for exit status\n", NULL, 255);
	}
	add_expanded(data, temp_str, exit_status_str);
	free(exit_status_str);
	exit_status_str = NULL;
}

// This function sets flags for single or double quotes.
// It calls expand_name if it finds a variable outside quotes
// or inside double quotes.
// Otherwise it just adds characters one by one to temp_str.
char	*expand_arg(t_data *data, char *arg)
{
	char	*temp_str;

	data->is_s_quoted = 0;
	data->is_d_quoted = 0;
	temp_str = ft_strdup("");
	if (!temp_str)
		snuff_it(data, "Error allocating memory for temp_str\n", NULL, 255);
	while (*arg)
	{
		if (*arg == '$' && !data->is_s_quoted)
		{
			if (*(arg + 1) == '\0' || *(arg + 1) == '\"' || *(arg + 1) == '\''
				|| ft_iswhitespace(*(arg + 1)))
				temp_str = add_one_char(data, &arg, temp_str);
			else if (*(arg + 1) == '?')
				get_exit_status(data, &temp_str, &arg);
			else if (!ft_isalpha(*(arg + 1)) && *(arg + 1) != '_')
				temp_str = add_one_char(data, &arg, temp_str);
			else
				expand_name(data, &arg, &temp_str);
		}
		else
			temp_str = add_one_char(data, &arg, temp_str);
	}
	return (temp_str);
}
