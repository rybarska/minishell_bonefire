/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 19:45:54 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/11 14:26:48 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_var(t_data *data)
{
	int		start_pos;
	char	*var_name;

	start_pos = data->pos;
	while (ft_isalnum_or_(data->text[data->pos]) || data->text[data->pos] == '$'
		|| data->text[data->pos] == '{' || data->text[data->pos] == '}')
		data->pos++;
	var_name = malloc(data->pos - start_pos + 1);
	if (!var_name)
		snuff_it(data, "Error allocating memory for var", NULL, 255);
	add_string_to_thrash_list(data, var_name);
	ft_strlcpy(var_name, data->text + start_pos, data->pos - start_pos + 1);
	return (var_name);
}

int	starts_next_token(int c)
{
	if (ft_iswhitespace(c) || c == '|' || c == '<' || c == '>' || c == '\"'
		|| c == '\'' || c == '$' || c == '\0')
		return (1);
	return (0);
}

char	*parse_word(t_data *data)
{
	int		start_pos;
	int		word_len;
	char	*word;

	start_pos = data->pos;
	word_len = 0;
	word = NULL;
	while (data->text[data->pos] && !starts_next_token(data->text[data->pos]))
	{
		data->pos++;
		word_len++;
	}
	if (word_len > 0)
	{
		word = (char *)malloc((word_len + 1) * sizeof(char));
		if (!word)
			snuff_it(data, "Error allocating memory for word\n", NULL, 255);
		add_string_to_thrash_list(data, word);
		ft_strlcpy(word, &(data->text[start_pos]), word_len + 1);
	}
	return (word);
}

char	*allocate_export_string(t_data *data)
{
	char	*word;
	char	*allocated_string;
	int		word_len;

	word = "export";
	word_len = ft_strlen(word);
	allocated_string = (char *)malloc((word_len + 1) * sizeof(char));
	if (!allocated_string)
		snuff_it(data, "Error allocating memory for string\n", NULL, 255);
	add_string_to_thrash_list(data, allocated_string);
	ft_strlcpy(allocated_string, word, word_len + 1);
	return (allocated_string);
}

t_token	get_next_token(t_data *data)
{
	if (data->pos >= data->text_len)
		return ((t_token){EOF_TOKEN, NULL, NULL, 0});
	else if (data->text[data->pos] == '\'')
		return ((t_token){SINGLE_QUOTE, parse_single_quotes(data), NULL, 0});
	else if (data->text[data->pos] == '\"')
		return ((t_token){DOUBLE_QUOTE, parse_double_quotes(data), NULL, 0});
	else if (data->text[data->pos] == '$')
		return ((t_token){VAR, parse_var(data), NULL, 0});
	else if (data->text[data->pos] == '|')
		return (data->pos++, (t_token){PIPE, NULL, NULL, 0});
	else if (data->text[data->pos] == '<')
		return (parse_in_redirections(data));
	else if (data->text[data->pos] == '>')
		return (parse_out_redirections(data));
	else if (ft_iswhitespace(data->text[data->pos]))
	{
		while (ft_iswhitespace(data->text[data->pos]))
			data->pos++;
		return ((t_token){WHITESPACE, NULL, NULL, 0});
	}
	else if (ft_strncmp(data->text + data->pos, "export", 6) == 0
		&& (starts_next_token(data->text[data->pos + 6])))
	{
		data->pos += 6;
		return ((t_token){EXPORT, allocate_export_string(data), NULL, 0});
	}
	else
		return ((t_token){WORD, parse_word(data), NULL, 0});
}
