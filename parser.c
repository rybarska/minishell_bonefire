/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 19:59:45 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/08 19:59:51 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_input(t_data *data)
{
	char	*input;

	input = readline("minishell> ");
	if (!input)
	{
		handle_eof(data);
		return ;
	}
	add_history(input);
	//printf("Input: %s\n", input);
	data->text = ft_strdup(input);
	free(input);
	if (!data->text)
		snuff_it(data, "Error allocating memory for input\n", NULL, 255);
	data->text_len = ft_strlen(data->text);
	data->pos = 0;
}
