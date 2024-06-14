/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:26 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 15:36:44 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_hashtable(t_data *data)
{
	data->hashtab = ft_calloc(sizeof(t_keyvalue *), HASHTABLE_SIZE);
	if (!data->hashtab)
	{
		ft_putstr_fd("Error: malloc failure at hashtable creation\n", 2);
		exit(255);
	}
	data->child_list_head = NULL;
	data->child_list_tail = NULL;
	data->env_vars_head = NULL;
	data->ft_environ = NULL;
	data->signal_mode = INTERACTIVE;
	data->pipe_num = -1;
	data->thrash_list_head = NULL;
}

void	init_data(t_data *data)
{
	data->exec_list_head = NULL;
	data->token_list_head = NULL;
	data->token_list_tail = NULL;
	data->pos = 0;
	data->text = NULL;
	data->text_len = -1;
	data->urandom = -1;
	data->cmd_paths = NULL;
	data->found_path = NULL;
	data->index = -1;
	data->exec_num = -1;
	data->fd[0] = -1;
	data->fd[1] = -1;
	data->std_in = -1;
	data->temp1_fd = -1;
	data->temp2_fd = -1;
	data->is_s_quoted = -1;
	data->is_d_quoted = -1;
	data->pid = -1;
	data->last_exit_code = 0;
	init_hashtable(data);
}
