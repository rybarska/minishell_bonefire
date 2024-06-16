/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 18:22:00 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:03 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "minishell.h"

static void	process_heredoc_vars(t_data *data, char **string)
{
	char	*expanded;

	if (ft_strchr(*string, '$'))
	{
		expanded = heredoc_expand_var(data, *string);
		free(*string);
		*string = expanded;
	}
}

// This is a custom rand function using /dev/urandom as source of random value.
// The random value is limited to INT_MAX in the return statement.
static int	get_rand_value(t_data *data)
{
	int		random_value;
	ssize_t	bytes;

	data->urandom = open("/dev/urandom", O_RDONLY);
	if (data->urandom < 0)
		snuff_it(data, "Error opening /dev/urandom\n", NULL, 255);
	bytes = read(data->urandom, &random_value, sizeof(random_value));
	if (bytes < 0)
		snuff_it(data, "Error reading from /dev/urandom\n", NULL, 255);
	close_fd_set_minus1(&data->urandom);
	return (random_value % INT_MAX);
}

// This function converts the random value returned from the previous function
// into a random string.
// The random string is incorporated into filenames to make them unique.
static void	init_temp_file(t_data *data, t_redirection *redir)
{
	char	temp_filename[MAX_FILENAME_LEN];
	char	*random_str;
	int		random_value;

	random_value = get_rand_value(data);
	random_str = NULL;
	random_str = ft_itoa(random_value);
	if (!random_str)
		snuff_it(data, "Error converting value to string\n", NULL, 255);
	add_string_to_thrash_list(data, random_str);
	ft_strlcpy(temp_filename, "temp_doc_", sizeof(temp_filename));
	ft_strlcat(temp_filename, random_str, sizeof(temp_filename));
	ft_strlcat(temp_filename, ".txt", sizeof(temp_filename));
	redir->file = ft_strdup(temp_filename);
	if (!redir->file)
		snuff_it(data, "Error creating temp_filename\n", NULL, 255);
	redir->fd = open(redir->file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd < 0)
		snuff_it(data, "Error creating temp_file\n", NULL, 255);
}

static void	write_temp_file(t_data *data, t_redirection *redir)
{
	char	*buffer;
	int		delimiter_len;

	delimiter_len = ft_strlen(redir->delimiter);
	buffer = get_next_line(data, 0);
	while (buffer != NULL)
	{
		if ((g_o_on == 2) || (ft_strlen(buffer) == delimiter_len
				&& ft_strncmp(buffer, redir->delimiter, delimiter_len) == 0))
			break ;
		process_heredoc_vars(data, &buffer);
		if ((write(redir->fd, buffer, ft_strlen(buffer)) < 0)
			|| (write(redir->fd, "\n", 1) < 0))
		{
			close_fd_set_minus1(&redir->fd);
			unlink(redir->file);
			free(buffer);
			snuff_it(data, "Error writing to here_doc\n", NULL, 255);
		}
		free(buffer);
		buffer = get_next_line(data, 0);
	}
	free(buffer);
	if (g_o_on == 2)
		g_o_on = 0;
}

void	get_heredoc(t_data *data, t_redirection **redir)
{
	set_mode(data, HERE_DOC);
	init_temp_file(data, *redir);
	write_temp_file(data, *redir);
	close_fd_set_minus1(&(*redir)->fd);
}
