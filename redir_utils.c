/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 16:25:59 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/15 16:26:01 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_lstadd_back(t_redirection **lst, t_redirection *new_redirection)
{
	t_redirection	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new_redirection;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_redirection;
}

void	set_rdr_file_or_delimiter(t_data *data, t_token_node *temp,
		t_redirection *new_rdr)
{
	if (new_rdr->type == 6 || new_rdr->type == 7 || new_rdr->type == 8)
	{
		new_rdr->file = ft_strdup(temp->value);
		if (!new_rdr->file)
		{
			free(new_rdr);
			new_rdr = NULL;
			snuff_it(data, "Error allocating memory for new_rdr->file", NULL,
				255);
		}
	}
	if (new_rdr->type == 9)
	{
		new_rdr->delimiter = ft_strdup(temp->value);
		if (!new_rdr->delimiter)
		{
			free(new_rdr);
			new_rdr = NULL;
			snuff_it(data, "Error allocating memory for new_rdr->delimiter",
				NULL, 255);
		}
	}
}

void	extend_redirection_lists(t_data *data, t_token_node *temp,
		t_exec **exec)
{
	t_redirection	*new_rdr;

	new_rdr = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_rdr)
		snuff_it(data, "Error allocating memory for new_rdr", NULL, 255);
	new_rdr->type = temp->type;
	new_rdr->file = NULL;
	new_rdr->delimiter = NULL;
	set_rdr_file_or_delimiter(data, temp, new_rdr);
	new_rdr->fd = -1;
	new_rdr->next = NULL;
	if (new_rdr->type == 6 || new_rdr->type == 9)
		redir_lstadd_back(&((*exec)->in_redirs), new_rdr);
	if (new_rdr->type == 7 || new_rdr->type == 8)
		redir_lstadd_back(&((*exec)->out_redirs), new_rdr);
}
