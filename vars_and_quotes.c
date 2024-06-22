/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_and_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:40:19 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/15 21:40:21 by arybarsk         ###   ########.fr       */
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

void	process_and_quote_vars(t_data *data, char **string)
{
	char	*expanded;

	if (ft_strchr(*string, '$'))
	{
		expanded = expand_arg(data, *string);
		free(*string);
		*string = ft_strjoin("\"", expanded);
		*string = ft_strjoin(*string, "\"");
		printf("string: %s\n", *string);
	}
}
