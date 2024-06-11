/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:57:43 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:13 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_o_on = 0;

void	handle_eof_or_ctrl_d(t_data *data)
{
	printf("exit\n");
	exit_like_a_boss(data, data->last_exit_code);
}

void	read_input(t_data *data)
{
	char	*input;

	input = NULL;
	set_mode(data, INTERACTIVE);
	printf("data->last_exit_code %d\n", data->last_exit_code);
	input = readline("minishell> ");
	if (g_o_on == 2)
	{
		data->last_exit_code = 130;
		g_o_on = 0;
	}
	add_string_to_thrash_list(data, input);
	set_mode(data, NON_INTERACTIVE);
	if (!input)
	{
		handle_eof_or_ctrl_d(data);
		return ;
	}
	add_history(input);
	data->text = ft_strdup(input);
	// free(input);
	// input = NULL;
	if (!data->text)
		snuff_it(data, "Error allocating memory for input\n", NULL, 255);
	data->text_len = ft_strlen(data->text);
	data->pos = 0;
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
		if (check_quote_syntax(&data) == 0)
		{
			make_token_list(&data);
			merge_unseparated(&data.token_list_head);
			count_pipes(&data);
			print_tokens(data.token_list_head);
			if (check_token_syntax(&data) == 0)
			{
				make_executives(&data);
				print_execs(data.exec_list_head);
				// print_envs(data.env_vars_head);
				if (count_executives(&data) > 0)
				{
					execute_execs(&data);
					// wait_for_children(&data);
				}
			}
		}
		clean_up_data(&data);
	}
	return (data.last_exit_code);
}
