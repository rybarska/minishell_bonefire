/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:22 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/13 15:38:24 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	boo(t_data *data, char *error_msg, char *name, int exit_code)
{
	if (name)
	{
		write(2, name, ft_strlen(name));
		write(2, ": ", 2);
	}
	write(2, error_msg, ft_strlen(error_msg));
	data->last_exit_code = exit_code;
	clean_up_data(data);
}

int	has_unquoted_equals(char *str)
{
	int	is_s_quoted;
	int	is_d_quoted;
	int	unquoted_equal;

	is_s_quoted = 0;
	is_d_quoted = 0;
	unquoted_equal = 0;
	while (*str)
	{
		if (*str == '\'' && !is_d_quoted)
			is_s_quoted = !is_s_quoted;
		if (*str == '\"' && !is_s_quoted)
			is_d_quoted = !is_d_quoted;
		if (*str == '=' && !is_s_quoted && !is_d_quoted)
			unquoted_equal = 1;
		str++;
	}
	return (unquoted_equal);
}
