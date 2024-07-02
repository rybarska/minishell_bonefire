/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:38:22 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/02 19:35:39 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	boo(t_data *data, char *error_msg, char *name, int exit_code)
{
	if (name)
	{
		write(2, "\'", 1);
		write(2, name, ft_strlen(name));
		write(2, "\'", 1);
		write(2, ": ", 2);
	}
	write(2, error_msg, ft_strlen(error_msg));
	data->last_exit_code = exit_code;
}

char	*ft_getenv(t_data *data, char *name)
{
	int		i;
	size_t	name_len;

	if (data == NULL || name == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	i = -1;
	while (data->ft_environ[++i] != NULL)
	{
		if (!ft_strncmp(data->ft_environ[i], name, name_len)
			&& data->ft_environ[i][name_len] == '=')
			return (data->ft_environ[i] + name_len + 1);
	}
	return (NULL);
}

int	has_unquoted_equals(char *str)
{
	int	is_s_quoted;
	int	is_d_quoted;
	int	unquoted_equal;

	is_s_quoted = 0;
	is_d_quoted = 0;
	unquoted_equal = 0;
	while (*str)
	{
		if (*str == '\'' && !is_d_quoted)
			is_s_quoted = !is_s_quoted;
		if (*str == '\"' && !is_s_quoted)
			is_d_quoted = !is_d_quoted;
		if (*str == '=' && !is_s_quoted && !is_d_quoted)
			unquoted_equal = 1;
		str++;
	}
	return (unquoted_equal);
}

void	count_pipes(t_data *data)
{
	int				pipe_counter;
	t_token_node	*current;

	pipe_counter = 0;
	current = data->token_list_head;
	while (current)
	{
		if (current->type == PIPE)
			pipe_counter++;
		current = current->next;
	}
	data->pipe_num = pipe_counter;
}

void	wait_for_children(t_data *data)
{
	t_process	*current;
	int			wait_result;
	bool		print_flag;

	current = data->child_list_head;
	print_flag = false;
	while (current != NULL)
	{
		wait_result = waitpid(current->child_pid, &current->status, WUNTRACED);
		if (wait_result < 0)
			snuff_it(data, "Error: waitpid failed\n", NULL, 255);
		if (WIFSIGNALED(current->status))
		{
			if (!print_flag)
				print_flag = write(STDOUT_FILENO, "\n", 1);
			data->last_exit_code = WTERMSIG(current->status) + 128;
		}
		else if (WIFEXITED(current->status))
			data->last_exit_code = WEXITSTATUS(current->status);
		else
			data->last_exit_code = current->status;
		current = current->next;
	}
}
