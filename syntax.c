/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 22:47:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/10 22:47:56 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quote_syntax(t_data *data)
{
	char	*temp_str;
	int	is_s_quoted;
	int	is_d_quoted;

	is_s_quoted = 0;
	is_d_quoted = 0;
	temp_str = data->text;
	while (*temp_str)
	{
		if (*temp_str == '\'' && !is_d_quoted)
			is_s_quoted = !is_s_quoted;
		if (*temp_str == '\"' && !is_s_quoted)
			is_d_quoted = !is_d_quoted;
		temp_str++;
	}
	if (is_s_quoted || is_d_quoted)
	{
		data->last_exit_code = 2;
		return (boo(data, "Syntax error near unexpected token\n", NULL, 2), 2);
	}
	return (0);
}

int	check_token_syntax(t_data *data)
{
	t_token_node	*current;

	current = data->token_list_head;
	if (current->type == EOF_TOKEN)
		return 0;
	while (current)
	{
		if (is_redirecting(current->type) && !(current->value))
			return (boo(data, "Syntax error near unexpected token\n", NULL, 2), 2);
		else if (current->type == PIPE && (current->previous == NULL
			|| current->next == NULL || current->next->type == EOF_TOKEN
			|| current->next->type == PIPE))
			return (boo(data, "Syntax error near unexpected token\n", NULL, 2), 2);
		else
			current = current->next;
	}
	return (0);
}
