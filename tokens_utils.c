/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:23:53 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:23 by mhuszar          ###   ########.fr       */
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
	if (type == INFILE || type == TRUNCATE || type == APPEND || type == HEREDOC)
		return (1);
	return (0);
}

int	is_substantive(t_token_type type)
{
	if (type == WORD || type == VAR || type == SINGLE_QUOTE
		|| type == DOUBLE_QUOTE || type == ASSIGNMENT || type == EXPORT)
		return (1);
	return (0);
}
