/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:05:24 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/26 21:05:26 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This function calls allocate_and_expand if it finds a variable name
// and otherwise returns NULL.
// It also keeps track of flags for single or double quotes.
static void	expand_name(t_data *data, char **var_value, char **temp_str) //TODO figure out what to do about 5 parametres
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
	free(temp_str);
	temp_str = temp;
	(*arg)++;
	return (temp_str);
}

static void	get_exit_status(t_data *data, char **temp_str, char **arg)
{
	char	*exit_status_str;

	(*arg) += 2;
	exit_status_str = ft_itoa(data->last_exit_code);
	if (!exit_status_str)
	{
		free(*temp_str);
		snuff_it(data, "Error allocating memory for exit status\n", NULL, 255);
	}
	add_expanded(data, temp_str, exit_status_str);
	free(exit_status_str);
}

/*void	free_temp_str_and_snuff_it(t_data *data, char **temp_str, char *arg)
{
	free(*temp_str);
	snuff_it(data, "Error allocating memory for var\n", arg, 255);
}*/

// This function sets flags for single or double quotes.
// It calls expand_name if it finds a variable outside quotes
// or inside double quotes.
// Otherwise it just adds characters one by one to temp_str.
// Btw expand_name calls allocate_and_expand. If there is malloc failure there
// then it returns 255, and then snuff_it is called here.
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
			if (*(arg + 1) == '\0' || ft_iswhitespace(*(arg + 1)))
				temp_str = add_one_char(data, &arg, temp_str);
			else if (*(arg + 1) == '?')
				get_exit_status(data, &temp_str, &arg);
			else
				expand_name(data, &arg, &temp_str);
		}
		else
			temp_str = add_one_char(data, &arg, temp_str);
	}
	return (temp_str);
}
