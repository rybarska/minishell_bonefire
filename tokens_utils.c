/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:23:53 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/26 18:23:55 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separating(t_token_type type)
{
	if (type == WHITESPACE || type == PIPE || type == INFILE || type == TRUNCATE
		|| type == APPEND || type == HEREDOC || type == EOF_TOKEN)
		return (1);
	return (0);
}

int	is_redirecting(t_token_type type)
{
	if ( type == INFILE || type == TRUNCATE || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_substantive(t_token_type type)
{
	if ( type == WORD || type == VAR || type == SINGLE_QUOTE || type == DOUBLE_QUOTE
		|| type == ASSIGNMENT)
		return (1);
	return (0);
}

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
	if (ft_strchr(*string, '\'')
		|| ft_strchr(*string, '\"'))
	{
		quotes_rm = rm_quotes(data, *string);
		free(*string);
		*string = quotes_rm;
	}
}
