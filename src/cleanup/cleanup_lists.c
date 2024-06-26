/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_lists.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:36:08 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/03 14:36:15 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_lstclear(t_process **lst)
{
	t_process	*current;
	t_process	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	redir_lstclear(t_redirection **lst)
{
	t_redirection	*current;
	t_redirection	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (current->delimiter)
		{
			free(current->delimiter);
			current->delimiter = NULL;
			if (current->file)
				unlink(current->file);
		}
		if (current->file)
			free(current->file);
		current->file = NULL;
		close_fd_set_minus1(&current->fd);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	redir_lst_close_fds(t_redirection **lst)
{
	t_redirection	*current;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		if (current->file)
			free(current->file);
		current->file = NULL;
		if (current->delimiter)
			free(current->delimiter);
		current->delimiter = NULL;
		if (current->fd >= 0)
			close_fd_set_minus1(&current->fd);
		free(current);
		current = current->next;
	}
}

void	exec_lstclear(t_exec **lst)
{
	t_exec	*current;
	t_exec	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (current->name)
			free(current->name);
		current->name = NULL;
		if (current->cmd_exec_path)
			free(current->cmd_exec_path);
		current->cmd_exec_path = NULL;
		if (current->arguments)
			ft_free_array(current->arguments);
		redir_lstclear(&current->in_redirs);
		redir_lstclear(&current->out_redirs);
		free(current);
		current = next;
	}
	*lst = NULL;
}

void	token_node_lstclear(t_token_node **lst)
{
	t_token_node	*current;
	t_token_node	*next;

	if (!lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		if (current->value)
			free(current->value);
		current->value = NULL;
		if (current->split_words)
			ft_free_array(current->split_words);
		free(current);
		current = next;
	}
	*lst = NULL;
}
