/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:57:59 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:27:07 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_quotes(t_data *data)
{
	if (data->text[data->pos] == '\'' && !data->is_d_quoted)
		data->is_s_quoted = !data->is_s_quoted;
	if (data->text[data->pos] == '\"' && !data->is_s_quoted)
		data->is_d_quoted = !data->is_d_quoted;
}

static void	parse_filename_inner(t_data *data)
{
	while (data->pos < data->text_len && !(data->is_s_quoted)
		&& !(data->is_d_quoted) && data->text[data->pos] != ' '
		&& data->text[data->pos] != '\0' && data->text[data->pos] != '|'
		&& data->text[data->pos] != '<' && data->text[data->pos] != '>')
	{
		data->pos++;
		check_quotes(data);
	}
	while (data->pos < data->text_len && data->is_s_quoted)
	{
		data->pos++;
		check_quotes(data);
		if (!data->is_s_quoted)
			data->pos++;
	}
	while (data->pos < data->text_len && data->is_d_quoted)
	{
		data->pos++;
		check_quotes(data);
		if (!data->is_d_quoted)
			data->pos++;
	}
}

static char	*parse_filename(t_data *data)
{
	int		start_pos;
	int		word_len;
	char	*word;

	start_pos = data->pos;
	data->is_s_quoted = 0;
	data->is_d_quoted = 0;
	check_quotes(data);
	while (data->pos < data->text_len)
	{
		parse_filename_inner(data);
		if (data->text[data->pos] == '\0' || data->text[data->pos] == '\n'
			|| data->text[data->pos] == ' ' || data->text[data->pos] == '|'
			|| data->text[data->pos] == '<' || data->text[data->pos] == '>')
			break ;
	}
	word_len = data->pos - start_pos;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		snuff_it(data, "Error allocating memory for filename\n", NULL, 255);
	ft_strlcpy(word, &(data->text[start_pos]), word_len + 1);
	process_vars_and_quotes(data, &word);
	add_string_to_thrash_list(data, word);
	return (word);
}

t_token	parse_in_redirections(t_data *data)
{
	char	*delimiter;
	char	*infile_name;

	data->pos++;
	if (data->text[data->pos] == '<')
	{
		data->pos++;
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		delimiter = parse_delimiter(data);
		return ((t_token){HEREDOC, delimiter});
	}
	else
	{
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		infile_name = parse_filename(data);
		return ((t_token){INFILE, infile_name});
	}
}

t_token	parse_out_redirections(t_data *data)
{
	char	*outfile_name;

	data->pos++;
	if (data->text[data->pos] == '>')
	{
		data->pos++;
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		outfile_name = parse_filename(data);
		return ((t_token){APPEND, outfile_name});
	}
	else
	{
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		outfile_name = parse_filename(data);
		return ((t_token){TRUNCATE, outfile_name});
	}
}
