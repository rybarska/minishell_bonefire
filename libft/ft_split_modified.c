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

#include "libft.h"
#include <stdio.h>

int	count_words(char const *s, char *delimiters)
{
	int	words;

	words = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (ft_strchr(delimiters, *s)
			s++;
		if (*s)
			words++;
		while (!ft_strchr(delimiters, *s) && *s)
			s++;
	}
	return (words);
}

int	count_word_len(char const *s, char const *delimiters)
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

void	*free_whole_array(int i, char **array)
{
	while (i >= 0)
	{
		free(array[i]);
		i--;
	}
	free(array);
	return (NULL);
}

char	**ft_split(char const *s, char const *delimiters)
{
	int	i;
	char	**array;

	i = 0;
	array = (char **)malloc(sizeof(char *) * (count_words(s, delimiters) + 1));
	if (!(array))
		return (NULL);
	while (*s)
	{
		while (ft_strchr(delimiters, *s))
			s++;
		if (*s && count_word_len(s, delimiters) > 0)
		{
			array[i] = ft_substr(s, 0, count_word_len(s, delimiters));
			if (!(array[i]))
			{
				free_whole_array(i, array);
				return (NULL);
			}
			s += count_word_len(s, delimiters);
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}
/*
#include <stdio.h>
int	main(void)
{
	char	string[] = "ooooo go with the flow I tell you sooooo";
	char	c = 'o';
//	printf("%d\n", count_words(string, c));
	char	**array = ft_split(string, c);
	while (array)
		printf("%s\n", *array++);
	free_whole_array(4, array);
	return (0);
 } */
