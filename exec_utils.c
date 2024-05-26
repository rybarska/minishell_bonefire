/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:33:00 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/29 18:33:02 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*make_empty_exec(t_data *data)
{
	t_exec		*exec;

	exec = NULL;
	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		snuff_it(data, "Error allocating memory for exec\n", NULL, 255);
	exec->name = NULL;
	exec->cmd_exec_path = NULL;
	exec->is_full_path = 0;
	exec->in_redirs = NULL;
	exec->out_redirs = NULL;
	exec->arguments = NULL;
	exec->next = NULL;
	exec->previous = NULL;
	exec->is_export = 0;
	return (exec);
}

void	exec_lstadd_back(t_exec **lst, t_exec *new)
{
	t_exec	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new;
}

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

void	set_rdr_file_or_delimiter(t_data *data, t_token_node *temp, t_redirection *new_rdr)
{
	if (new_rdr->type == 6 || new_rdr->type == 7 || new_rdr->type == 8)
	{
		new_rdr->file = ft_strdup(temp->value);
		if (!new_rdr->file)
		{
			free(new_rdr);
			snuff_it(data, "Error allocating memory for new_rdr->file",
				NULL, 255);
		}	
	}
	if (new_rdr->type == 9)
	{
		new_rdr->delimiter = ft_strdup(temp->value);
		if (!new_rdr->delimiter)
		{
			free(new_rdr);
			snuff_it(data, "Error allocating memory for new_rdr->delimiter",
				NULL, 255);
		}
	}
}

void	extend_redirection_lists(t_data *data, t_token_node *temp, t_exec **exec)
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

int	count_executives(t_data *data)
{
	int	exec_counter;
	t_exec	*current;

	exec_counter = 0;
	current = data->exec_list_head;
	while (current != NULL)
	{
		//if (current->arguments[0] && !is_builtin(current->arguments[0]))
		exec_counter++;
		current = current->next;
	}
	data->exec_num = exec_counter;
	return (exec_counter);
}
