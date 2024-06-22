/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_and_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:40:19 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/22 17:06:07 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_vars_and_quotes(t_data *data, char **string)
{
	char	*expanded;
	char	*quotes_rm;

	if (ft_strchr(*string, '$'))
	{
		expanded = expand_arg(data, *string);
		free(*string);
		*string = expanded;
	}
	if (ft_strchr(*string, '\'') || ft_strchr(*string, '\"'))
	{
		quotes_rm = rm_quotes(data, *string);
		free(*string);
		*string = quotes_rm;
	}
}

void	process_vars(t_data *data, char **string)
{
	char	*expanded;

	if (ft_strchr(*string, '$'))
	{
		expanded = expand_arg(data, *string);
		free(*string);
		*string = expanded;
	}
}

void	process_quotes(t_data *data, char **string)
{
	char	*quotes_rm;

	if (ft_strchr(*string, '\'') || ft_strchr(*string, '\"'))
	{
		quotes_rm = rm_quotes(data, *string);
		free(*string);
		*string = quotes_rm;
	}
}

void	process_vars_and_put_them_in_quotes(t_data *data, char **string)
{
	char	*expanded;

	if (ft_strchr(*string, '$'))
	{
		expanded = expand_arg(data, *string);
		free(*string);
		if (expanded)
		{
			*string = ft_strjoin("\"", expanded);
			if (!*string)
				snuff_it(data, "Error allocating for strjoin\n", NULL, 255);
			free(expanded);
			*string = ft_strjoin_free(*string, '\"');
			if (!*string)
				snuff_it(data, "Error allocating for strjoin_free\n", NULL, 255);
		}
	}
}
