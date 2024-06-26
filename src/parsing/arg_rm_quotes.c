/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rm_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 21:21:16 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/26 21:21:18 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_rm_quotes(char *arg, char **temp_str)
{
	int	is_s_quoted;
	int	is_d_quoted;

	is_s_quoted = 0;
	is_d_quoted = 0;
	while (*arg)
	{
		if (*arg == '\"' && !is_s_quoted)
		{
			is_d_quoted = !is_d_quoted;
			arg++;
		}
		else if (*arg == '\'' && !is_d_quoted)
		{
			is_s_quoted = !is_s_quoted;
			arg++;
		}
		else
		{
			**temp_str = *arg;
			(*temp_str)++;
			arg++;
		}
	}
	**temp_str = '\0';
}

char	*rm_quotes(t_data *data, char *arg)
{
	char	*temp_str;
	char	*temp_str_start;

	temp_str = (char *)malloc((ft_strlen(arg) + 1) * sizeof(char));
	if (!temp_str)
		snuff_it(data, "Error allocating memory for temp_str\n", NULL, 255);
	temp_str_start = temp_str;
	check_rm_quotes(arg, &temp_str);
	return (temp_str_start);
}
