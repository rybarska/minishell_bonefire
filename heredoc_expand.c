/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 20:16:14 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/10 20:16:16 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	heredoc_add_expanded(char **temp_str, char *expanded)
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
	expanded_dup = NULL;
	free(*temp_str);
	if (!temp)
		return (255);
	*temp_str = temp;
	return (0);
}

// This function calls ft_getenv and returns either the expanded var or NULL
static int	heredoc_allocate_and_expand(t_data *data, char **temp_str, char *var_name_start,
	char *var_name_end)
{
	char	*var_name;
	char	*expanded;

	expanded = NULL;
	var_name = NULL;
	var_name = (char *)malloc(sizeof(char)
			* (var_name_end - var_name_start + 1));
	if (!var_name)
		return (255);
	ft_strlcpy(var_name, var_name_start, var_name_end - var_name_start + 1);
	expanded = ft_getenv(data, var_name);
	free(var_name);
	var_name = NULL;
	if (expanded)
	{
		if (heredoc_add_expanded(temp_str, expanded) == 255)
			return (255);
	}
	return (0);
}

// This function calls allocate_and_expand if it finds a variable name
// and otherwise returns NULL.
// It also keeps track of flags for single or double quotes.
static int	expand_name(t_data *data, char **var_value, char **temp_str, int *is_d_quoted,
	int *is_s_quoted)//TODO figure out what to do about 5 parametres
{
	char	*var_name_start;
	char	*var_name_end;

	(*var_value)++;
	if (**var_value == '{')
		(*var_value)++;
	var_name_start = *var_value;
	var_name_end = var_name_start;
	while (*var_name_end && !ft_strchr(" \t\"\'$}", *var_name_end))
	{
		if (*var_name_end == '\'' && !is_d_quoted)
			*is_s_quoted = !*is_s_quoted;
		if (*var_name_end == '\"' && !is_s_quoted)
			*is_d_quoted = !*is_d_quoted;
		var_name_end++;
		(*var_value)++;
	}
	if (*var_name_end == '}')
		(*var_value)++;
	if (var_name_end != var_name_start)
	{
		if (heredoc_allocate_and_expand(data, temp_str, var_name_start, var_name_end) > 0)
			return (255);
	}
	return (0);
}

static char	*add_one_char(char **arg, char *temp_str,  int *is_d_quoted,
	int *is_s_quoted)
{
	char	*temp;

	temp = NULL;
	if (**arg == '\'' && !*is_d_quoted)
		*is_s_quoted = !*is_s_quoted;
	if (**arg == '\"' && !*is_s_quoted)
		*is_d_quoted = !*is_d_quoted;
	temp = ft_strjoin_char(temp_str, **arg);
	free(temp_str);
	temp_str = temp;
	(*arg)++;
	return (temp_str);
}

// This function sets flags for single or double quotes.
// It calls expand_name if it finds a variable outside quotes
// or inside double quotes.
// Otherwise it just adds characters one by one to temp_str.
// Btw expand_name calls allocate_and_expand. If there is malloc failure there
// then it returns 255, and then snuff_it is called here.
char	*heredoc_expand_var(t_data *data, char *arg)
{
	char	*temp_str;
	int	is_s_quoted;
	int	is_d_quoted;

	is_s_quoted = 0;
	is_d_quoted = 0;
	temp_str = ft_strdup("");
	if (!temp_str)
		snuff_it(data, "Error allocating memory for temp_str\n", NULL, 255);
	while (*arg)
	{
		if (*arg == '$')
		{
			if (expand_name(data, &arg, &temp_str, &is_d_quoted, &is_s_quoted) == 255)
			{
				free(temp_str);
				temp_str = NULL;
				snuff_it(data, "Error allocating memory for var\n",
					NULL, 255);
			}
		}
		else
			temp_str = add_one_char(&arg, temp_str, &is_d_quoted, &is_s_quoted);
	}
	return (temp_str);
}
