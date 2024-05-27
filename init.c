/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:41:26 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/21 18:41:32 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	data->pid = -1;
	data->last_exit_code = 0;
	data->child_list_head = NULL;
	data->child_list_tail = NULL;
	data->env_vars_head = NULL;
	data->ft_environ = NULL;
}
