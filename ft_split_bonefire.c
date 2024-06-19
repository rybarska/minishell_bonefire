/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 11:29:13 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/19 20:47:08 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s, char c)
{
	int	words;

	words = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

static int	count_word_len(t_data *data, char const *s, char c)
{
	int	word_len;

	word_len = 0;
	while (*s == c)
		s++;
	if (*s == '\'' && !data->is_d_quoted)
		data->is_s_quoted = !data->is_s_quoted;
	if (*s == '\"' && !data->is_s_quoted)
		data->is_d_quoted = !data->is_d_quoted;
	while (*s != c && *s != '\0')
	{
		word_len++;
		s++;
	}
	return (word_len);
}

char	**ft_split_bonefire(t_data *data, char *s, int *elements)
{
	int		i;
	char	**array;
	char 	c;

	data->is_s_quoted = 0;
	data->is_d_quoted = 0;
	c = ' ';
	i = 0;
	*elements = count_words(s, c);
	array = (char **)malloc(sizeof(char *) * (*elements + 1));
	if (!(array))
		snuff_it(data, "Error allocating for split\n", NULL, 255);
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && count_word_len(data, s, c) > 0)
		{
			array[i] = ft_substr(s, 0, count_word_len(data, s, c));
			if (!(array[i]))
			{
				ft_free_array(array);
				snuff_it(data, "Error allocating for split\n", NULL, 255);
			}
			s += count_word_len(data, s, c);
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}
