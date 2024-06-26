/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonefire.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:54:07 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/25 21:54:09 by arybarsk         ###   ########.fr       */
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

static int	count_word_len(char const *s, char c)
{
	int	word_len;

	word_len = 0;
	while (*s == c)
		s++;
	while (*s != c && *s != '\0')
	{
		s++;
		word_len++;
	}
	return (word_len);
}

static void	skip_whitespace(char **s)
{
	while (**s == ' ')
		(*s)++;
}

char	**ft_split_bonefire_regular(t_data *data, char *s, int *elements)
{
	int		i;
	char	**array;

	i = 0;
	*elements = count_words(s, ' ');
	array = (char **)malloc(sizeof(char *) * (*elements + 1));
	if (!(array))
		snuff_it(data, "Error allocating memory \n", NULL, 255);
	while (*s)
	{
		skip_whitespace(&s);
		if (*s && count_word_len(s, ' ') > 0)
		{
			array[i] = ft_substr(s, 0, count_word_len(s, ' '));
			if (!(array[i]))
			{
				ft_free_array(array);
				snuff_it(data, "Error allocating memory \n", NULL, 255);
			}
			s += count_word_len(s, ' ');
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}
