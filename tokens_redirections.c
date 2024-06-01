/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 15:57:59 by arybarsk          #+#    #+#             */
/*   Updated: 2024/03/15 15:58:01 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_filename(t_data *data)
{
	int	start_pos;
	int	word_len;
	char	*word;

	start_pos = data->pos;
	if (data->pos < data->text_len && (data->text[data->pos] == '\n'
		|| data->text[data->pos] == '\0' || data->text[data->pos] == '|'
		|| data->text[data->pos] == '<' || data->text[data->pos] == '>'))
			return (NULL);
	while (data->pos < data->text_len && data->text[data->pos] != ' '
		&& data->text[data->pos] != '\0' && data->text[data->pos] != '|'
		&& data->text[data->pos] != '<' && data->text[data->pos] != '>')
			data->pos++;
	word_len = data->pos - start_pos;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		snuff_it(data, "Error allocating memory for filename\n", NULL, 255);
	add_string_to_thrash_list(data, word);
	ft_strlcpy(word, &(data->text[start_pos]), word_len + 1);
	process_vars_and_quotes(data, &word);
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
		return ((t_token){HEREDOC, delimiter, NULL, 0});
	}
	else
	{
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		infile_name = parse_filename(data);
		return ((t_token){INFILE, infile_name, NULL, 0});
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
		return ((t_token){APPEND, outfile_name, NULL, 0});
	}
	else
	{
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		outfile_name = parse_filename(data);
		return ((t_token){TRUNCATE, outfile_name, NULL, 0});
	}
}
