/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:57:43 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/27 12:52:29 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_o_on = 0;

void	handle_eof_or_ctrl_d(t_data *data)
{
	printf("exit\n");
	exit_like_a_boss(data, data->last_exit_code);
}

void	handle_whitespace(t_data *data, char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '\0' || *str == '\n')
		return ;
	else
	{
		data->text = ft_strdup(str);
		if (!data->text)
			snuff_it(data, "Error allocating memory for input\n", NULL, 255);
		data->text_len = ft_strlen(data->text);
		data->pos = 0;
	}
}

void	read_input(t_data *data)
{
	char	*input;

	input = NULL;
	set_mode(data, INTERACTIVE);
	input = readline("minishell> ");
	if (g_o_on == 2)
	{
		data->last_exit_code = 130;
		g_o_on = 0;
	}
	add_string_to_thrash_list(data, input);
	set_mode(data, NON_INTERACTIVE);
	if (!input)
		handle_eof_or_ctrl_d(data);
	add_history(input);
	handle_whitespace(data, input);
}

int	main(void)
{
	t_data	data;

	init_data(&data);
	data.ft_environ = ft_strdup_array(environ);
	if (!data.ft_environ)
		snuff_it(&data, "Error: ft_strdup_array failed\n", NULL, 255);
	set_signal_controls(&data);
	while (1)
	{
		get_all_cmd_paths(&data);
		read_input(&data);
		if (data.text && !check_q_syntax(&data) && !check_r_syntax(&data))
		{
			make_token_list(&data);
			merge_unseparated(&data);
			count_pipes(&data);
			if (check_token_syntax(&data) == 0)
			{
				make_executives(&data);
				if (count_executives(&data) > 0)
					execute_execs(&data);
			}
		}
		clean_up_data(&data);
	}
}
