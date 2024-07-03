/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 18:51:45 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/26 18:51:48 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_flag(t_data *data, t_token_node *curr, int flag_for_quotes)
{
	int	i;

	if (!flag_for_quotes)
	{
		curr->split_words = ft_split_bonefire(data,
				curr->value, &curr->num_split_words);
		if (!curr->split_words)
			snuff_it(data, "Error allocating for split\n", NULL, 255);
		i = -1;
		while (curr->split_words[++i])
			process_quotes(data, &curr->split_words[i]);
	}
	else
	{
		curr->split_words = ft_split_bonefire_regular(data,
				curr->value, &curr->num_split_words);
		if (!curr->split_words)
			snuff_it(data, "Error allocating for split\n", NULL, 255);
	}
}

void	expand_and_split_and_process_quotes(t_data *data)
{
	t_token_node	*curr;
	int				flag_for_quotes;

	curr = data->token_list_head;
	flag_for_quotes = 0;
	while (curr)
	{
		if (is_substantive(curr->type) && curr->value)
		{
			if (ft_strchr(curr->value, '$') && !ft_strchr(curr->value, '\'')
				&& !ft_strchr(curr->value, '\"'))
				flag_for_quotes = 1;
			process_vars(data, &curr->value);
			if (!ft_strchr(curr->value, '$') && flag_for_quotes == 1
				&& (ft_strchr(curr->value, '\'')
					|| ft_strchr(curr->value, '\"')))
				flag_for_quotes = 1;
			else
				flag_for_quotes = 0;
			check_flag(data, curr, flag_for_quotes);
		}
		curr = curr->next;
	}
}
