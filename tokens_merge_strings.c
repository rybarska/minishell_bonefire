/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_merge_strings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 16:54:02 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/10 16:54:05 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_space_tokens(t_token_node **head)
{
	t_token_node	*curr;
	t_token_node	*prev;
	t_token_node	*temp;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (curr->type == 0)
		{
			if (prev)
				prev->next = curr->next;
			temp = curr;
			curr = curr->next;
			free(temp);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

void	merge_token_strings(t_token_node **current, t_token_node **prev)
{
	char	*merged_value;

	if (!(*prev))
		return ;
	merged_value = ft_strjoin((*prev)->value, (*current)->value);
	if (!merged_value)
		return ;
	free((*prev)->value);
	(*prev)->value = merged_value;
	(*prev)->type = (*current)->type;
	(*prev)->next = (*current)->next;
	if ((*current)->next != NULL)
		(*current)->next->previous = *prev;
	free((*current)->value);
	free(*current);
	*current = (*prev)->next;
}

void	check_assign_type(t_token_node **head)
{
	t_token_node	*curr;

	curr = *head;
	while (curr)
	{	
		if (is_substantive(curr->type) && has_unquoted_equals(curr->value))
			curr->type = ASSIGNMENT;
		/*if ((curr->type == EXPORT || curr->type == ASSIGNMENT)
			&& ft_strchr(curr->value, ' '))
			curr->split_words = ft_split(curr->value, ' ');*/
		curr = curr->next;
	}
}

void	merge_unseparated(t_token_node **head)
{
	t_token_node	*curr;
	t_token_node	*prev;

	curr = *head;
	prev = NULL;
	while (curr)
	{
		if (prev && !is_separating(prev->type) && !is_separating(curr->type))
			merge_token_strings(&curr, &prev);
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	check_assign_type(head);
	remove_space_tokens(head);
}
