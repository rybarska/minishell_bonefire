/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_to_execs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 21:39:12 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/13 21:39:16 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_token(t_data *data, t_token_node **temp,
	t_exec **exec)
{
	t_token_node	*current;
	int		arg_count;

	current = *temp;
	arg_count = 0;
	while (*temp && (*temp)->value)
	{
		if (*temp && (is_substantive((*temp)->type) || (*temp)->type == EXPORT))
			++arg_count;
		if (*temp && is_redirecting((*temp)->type))
			extend_redirection_lists(data, *temp, exec);
		*temp = (*temp)->next;
	}
	if (arg_count)
		put_cmd_in_exec(data, current, arg_count, exec);
}

void	process_cmd_and_redir_tokens(t_data *data, t_token_node **temp,
	t_exec **exec)
{
	while (*temp != NULL)
	{
		if ((*temp)->type == EXPORT)
		{
			(*exec)->is_export = 1;
			handle_command_token(data, temp, exec);
		}
		else if ((*temp)->type == ASSIGNMENT)
		{
			put_env_in_list(data, *temp, 1, 0);
			*temp = (*temp)->next;
		}
		else if (is_substantive((*temp)->type))
			handle_command_token(data, temp, exec);
		else if (is_redirecting((*temp)->type))
		{
			extend_redirection_lists(data, *temp, exec);
			*temp = (*temp)->next;
		}
		else
		{
			*temp = (*temp)->next;
			break ;
		}
	}
}

void	make_executives(t_data *data)
{
	t_token_node	*current;
	t_token_node	*temp;
	t_exec			*exec;
	t_exec			*exec_head;

	current = data->token_list_head;
	if (current->type == EOF_TOKEN)
		return ;
	exec_head = NULL;
	while (current != NULL)
	{
		temp = current;
		exec = make_empty_exec(data);
		process_cmd_and_redir_tokens(data, &temp, &exec);
		if ((exec->arguments == NULL || exec->arguments[0] == NULL)
			&& exec->in_redirs == NULL && exec->out_redirs == NULL)
			free(exec);
		else
			exec_lstadd_back(&exec_head, exec);
		current = temp;
	}
	data->exec_list_head = exec_head;
}
