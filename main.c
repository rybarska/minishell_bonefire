/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:57:43 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/10 19:57:46 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_o_on = 1;

static void	wait_for_children(t_data *data)
{
	t_process	*current;
	int		last_exit_code;

	current = data->child_list_head;
	last_exit_code = 0;
	while (current != NULL)
	{
		if (waitpid(current->child_pid, &current->status, WUNTRACED) < 0)
			snuff_it(data, "Error: waitpid failed\n", NULL, 255);
		if (WIFSIGNALED(current->status))
			last_exit_code = WTERMSIG(current->status) + 128;
		if (WIFEXITED(current->status))
			last_exit_code = WEXITSTATUS(current->status);
		current = current->next;;
	}
	data->last_exit_code = last_exit_code;
}

int	main(void)
{
	t_data		data;

	init_data(&data);
	data.ft_environ = ft_strdup_array(environ);
	if (!data.ft_environ)
		snuff_it(&data, "Error: ft_strdup_array failed\n", NULL, 255);
	set_signal_controls(&data);
	while (g_o_on)
	{
		get_all_cmd_paths(&data);
		read_input(&data);
		if (check_quote_syntax(&data) == 0)
		{
			make_token_list(&data);
			merge_unseparated(&data.token_list_head);
			print_tokens(data.token_list_head);
			if (check_token_syntax(&data) == 0)
			{
				make_executives(&data);
				print_execs(data.exec_list_head);
				print_envs(data.env_vars_head);
				if (count_executives(&data) > 0)
				{
					execute_execs(&data);
					wait_for_children(&data);
				}
			}
		}
		clean_up_data(&data);
	}
	return (data.last_exit_code);
}
