/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_merge_strings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:54:02 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:00 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_and_split_and_process_quotes(t_data *data)
{
	t_token_node	*curr;
	int				i;

	curr = data->token_list_head;
	while (curr)
	{
		if (is_substantive(curr->type) && curr->value)
		{
			process_vars_and_put_them_in_quotes(data, &curr->value);
			curr->split_words = ft_split_returns(data,
					curr->value, &curr->num_split_words);
			if (!curr->split_words)
				snuff_it(data, "Error allocating for split\n", NULL, 255);
			i = -1;
			while (curr->split_words[++i])
				process_quotes(data, &curr->split_words[i]);
		}
		curr = curr->next;
	}
}

void	remove_space_tokens(t_data *data)
{
	t_token_node	*curr;
	t_token_node	*prev;
	t_token_node	*temp;

	curr = data->token_list_head;
	prev = NULL;
	temp = NULL;
	while (curr)
	{
		if (curr->type == 0)
		{
			if (prev)
				prev->next = curr->next;
			temp = curr;
			curr = curr->next;
			free(temp);
			temp = NULL;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	merge_token_strings(t_data *data, t_token_node **current,
		t_token_node **prev)
{
	char	*merged_value;

	if (!(*prev))
		return ;
	merged_value = ft_strjoin((*prev)->value, (*current)->value);
	if (!merged_value)
		snuff_it(data, "Error allocating memory for merged value\n", NULL, 255);
	free((*prev)->value);
	(*prev)->value = merged_value;
	(*prev)->type = (*current)->type;
	(*prev)->next = (*current)->next;
	if ((*current)->next != NULL)
		(*current)->next->previous = *prev;
	free((*current)->value);
	(*current)->value = NULL;
	free(*current);
	*current = (*prev)->next;
}

void	check_assign_type(t_data *data)
{
	t_token_node	*curr;

	curr = data->token_list_head;
	while (curr)
	{
		if (is_substantive(curr->type) && has_unquoted_equals(curr->value))
			curr->type = ASSIGNMENT;
		curr = curr->next;
	}
}

void	merge_unseparated(t_data *data)
{
	t_token_node	*curr;
	t_token_node	*prev;

	curr = data->token_list_head;
	prev = NULL;
	while (curr)
	{
		if (prev && !is_separating(prev->type) && !is_separating(curr->type))
			merge_token_strings(data, &curr, &prev);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	check_assign_type(data);
	remove_space_tokens(data);
	expand_and_split_and_process_quotes(data);
}
