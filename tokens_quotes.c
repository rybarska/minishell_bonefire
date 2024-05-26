/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:51:44 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/07 18:51:48 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_single_quotes(t_data *data)
{
	int	start_pos;
	int	word_len;
	char	*word;

	start_pos = data->pos;
	data->pos++;
	while (data->text[data->pos] != '\0')
	{
		if (data->text[data->pos] == '\'')
		{
			data->pos++;
			break ;
		}
		data->pos++;
	}
	word_len = data->pos - start_pos;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		snuff_it(data, "Error allocating memory for single quotes\n", NULL, 255);
	ft_strlcpy(word, &(data->text[start_pos]), word_len + 1);
	return (word);
}

char	*parse_double_quotes(t_data *data)
{
	int	start_pos;
	int	word_len;
	char	*word;

	start_pos = data->pos;
	data->pos++;
	while (data->text[data->pos] != '\0')
	{
		if (data->text[data->pos] == '\"')
		{
			data->pos++;
			break ;
		}
		data->pos++;
	}
	word_len = data->pos - start_pos;
	word = (char *)malloc((word_len + 1) * sizeof(char));
	if (!word)
		snuff_it(data, "Error allocating memory for double quotes\n", NULL, 255);
	ft_strlcpy(word, &(data->text[start_pos]), word_len + 1);
	return (word);
}
