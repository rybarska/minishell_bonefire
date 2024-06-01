/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_delimiter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 23:16:15 by arybarsk          #+#    #+#             */
/*   Updated: 2024/04/26 23:16:20 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*parse_double_quotes_delimiter(t_data *data)
{
	int		start_pos;
	char	*word;

	data->pos++;
	start_pos = data->pos;
	while (data->text[data->pos] != '\0'
		&& data->text[data->pos] != '\"')
		data->pos++;
	if (data->text[data->pos] == '\"')
		data->pos++;
	word = ft_substr(data->text, start_pos, data->pos - 1 - start_pos);
	if (!word)
		snuff_it(data, "Error allocating memory for delimiter", NULL, 255);
	add_string_to_thrash_list(data, word);
	return (word);
}

static char	*parse_delimiter_inner(t_data *data)
{
	char	*temp;

	temp = NULL;
	if (data->text[data->pos] == '\'')
		temp = parse_single_quotes(data);
	else if (data->text[data->pos] == '\"')
		temp = parse_double_quotes_delimiter(data);
	else if (ft_isalnum_or_(data->text[data->pos]))
		temp = parse_word(data);
	else if (data->text[data->pos] == '$')
	{
		data->pos++;
		if (data->text[data->pos] == '\''
			|| data->text[data->pos] == '\"')
			temp = ft_strdup("");
		else
			temp = ft_strdup("$");
		add_string_to_thrash_list(data, temp);
	}
	else
		snuff_it(data, "Error in delimiter", NULL, 2);
	return (temp);
}

char	*parse_delimiter(t_data *data)
{
	int	start_pos;
	char	*delimiter;
	char	*temp;
	char	*temp_delimiter;
	char	current_char;

	delimiter = NULL;
	temp = NULL;
	start_pos = data->pos;
	current_char = data->text[data->pos];
	delimiter = ft_strdup("");
	if (!delimiter)
		snuff_it(data, "Error allocating memory for delimiter", NULL, 255);
	while (ft_iswhitespace(current_char))
	{
		data->pos++;
		current_char = data->text[data->pos];
	}
	if (ft_strchr("|><\n", data->text[data->pos]))
		return (NULL);
	while (data->text[data->pos]
		&& !ft_strchr("|>< \n", data->text[data->pos]))
	{
		temp = parse_delimiter_inner(data);
		//add_string_to_thrash_list(data, temp);
		temp_delimiter = ft_strjoin(delimiter, temp);
		if (!temp_delimiter)
			snuff_it(data, "Error allocating memory for temp_delimiter", NULL, 255);
		free(delimiter);
		delimiter = temp_delimiter;
		//free(temp);
		//temp = NULL;
	}
	add_string_to_thrash_list(data, delimiter);
	return (delimiter);
}
