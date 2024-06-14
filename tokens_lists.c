/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 20:55:44 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:29:25 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_token_list(t_data *data)
{
	t_token_node	*current;
	t_token_node	*next;

	current = data->token_list_head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		current->value = NULL;
		free(current);
		current = next;
	}
	data->token_list_head = NULL;
	data->token_list_tail = NULL;
}

static t_token_node	*create_token_node(t_data *data, t_token *new_token)
{
	t_token_node	*new_node;

	new_node = malloc(sizeof(t_token_node));
	if (!new_node)
		snuff_it(data, "Error allocating memory for new_node", NULL, 255);
	new_node->type = 0;
	new_node->type = new_token->type;
	new_node->value = NULL;
	if (new_token->value)
	{
		new_node->value = ft_strdup(new_token->value);
		if (!new_node->value)
			snuff_it(data, "Error duplicating string", NULL, 255);
	}
	new_node->split_words = NULL;
	new_node->num_split_words = 0;
	new_node->previous = NULL;
	new_node->next = NULL;
	return (new_node);
}

static void	add_token_node(t_data *data, t_token_node *new_node)
{
	if (new_node == NULL)
		snuff_it(data, "Error creating new_node", NULL, 2);
	if (data->token_list_head == NULL)
	{
		data->token_list_head = new_node;
		data->token_list_tail = new_node;
	}
	else
	{
		new_node->previous = data->token_list_tail;
		data->token_list_tail->next = new_node;
		data->token_list_tail = new_node;
	}
}

void	make_token_list(t_data *data)
{
	t_token			new_token;
	t_token_node	*new_node;

	new_token.type = WHITESPACE;
	while (1)
	{
		new_token = get_next_token(data);
		new_node = create_token_node(data, &new_token);
		add_token_node(data, new_node);
		if (new_token.type == EOF_TOKEN)
		{
			new_node = NULL;
			break ;
		}
	}
}
