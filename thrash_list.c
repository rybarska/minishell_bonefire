/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thrash_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:47:45 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/30 22:47:47 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_thrash_list(t_data *data)
{
	t_thrash_node	*current;
	t_thrash_node	*next;

	current = data->thrash_list_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	data->thrash_list_head = NULL;
}

static t_thrash_node	*create_thrash_node(t_data *data, char *string)
{
	t_thrash_node	*new_node;

	if (!string)
		return (NULL);
	new_node = malloc(sizeof(t_thrash_node));
	if (!new_node)
		snuff_it(data, "Error creating thrash node", NULL, 255);
	new_node->value = string;
	if (new_token->value)
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_thrash_node_to_list(t_data *data, t_thrash_node *new_node)
{
	if (new_node == NULL)
		return ;
	current = data->thrash_list_head;
	if (current == NULL)
		current = new_node;
	else
	{
		while (current)
			current = current->next;
		current = new_node;
	}
	current->next = NULL;
}

void	add_string_to_thrash_list(t_data *data, char *string)
{
	t_thrash_node	*new_node;
	t_thrash_node	*current;

	current = data->thrash_list_head;
	new_node = create_thrash_node(data, string);
	add_thrash_node_to_list(data, new_node);
}