/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thrash_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 22:47:45 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:39 by mhuszar          ###   ########.fr       */
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
		if (current->value)
		{
			free(current->value);
			current->value = NULL;
		}
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
	{
		free(string);
		string = NULL;
		snuff_it(data, "Error creating thrash node", NULL, 255);
	}
	new_node->value = NULL;
	new_node->value = string;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_thrash_node_to_list(t_data *data, t_thrash_node *new_node)
{
	t_thrash_node	*current;

	if (new_node == NULL)
		return ;
	if (data->thrash_list_head == NULL)
		data->thrash_list_head = new_node;
	else
	{
		current = data->thrash_list_head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->previous = current;
	}
}

void	add_string_to_thrash_list(t_data *data, char *string)
{
	t_thrash_node	*new_node;

	new_node = create_thrash_node(data, string);
	add_thrash_node_to_list(data, new_node);
}
