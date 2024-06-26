/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonefire.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:16:59 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/24 17:17:00 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_through_quotes_and_count(char *str, int *i,
			int *word_count, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
	(*word_count)++;
}

static void	get_through_unquoted_and_count(char *str, int *i, int *word_count)
{
	while (str[*i] && ft_iswhitespace(str[*i]))
		(*i)++;
	if (str[*i] && str[*i] != '\"' && str[*i] != '\'')
		(*word_count)++;
	while (str[*i] && str[*i] != '\"' && str[*i] != '\''
		&& !ft_iswhitespace(str[*i]))
		(*i)++;
}

static void	get_through_word_to_allocate(char *str, int *i, int *j)
{
	if (str[*i] == '\"')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\"')
			(*i)++;
	}
	else if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
	}
	else
	{
		while (str[*i] && ft_iswhitespace(str[*i]))
			(*i)++;
		*j = *i;
		while (str[*i] && str[*i] != '\"' && str[*i] != '\''
			&& !ft_iswhitespace(str[*i]))
			(*i)++;
	}
}

static char	**alloc_array_and_words(t_data *data, char *str, int word_count)
{
	int		i;
	int		j;
	int		k;
	char	**array;

	i = 0;
	j = 0;
	k = 0;
	array = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!array)
		snuff_it(data, "Error allocating memory \n", NULL, 255);
	while (str[i])
	{
		get_through_word_to_allocate(str, &i, &j);
		if ((str[i] == '\0' || ft_iswhitespace(str[i])) && i > j)
		{
			array[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!array[k])
				snuff_it(data, "Error allocating memory \n", NULL, 255);
			ft_strncpy(array[k++], &str[j], i - j);
			j = i;
		}
	}
	array[k] = NULL;
	return (array);
}

char	**ft_split_bonefire(t_data *data, char *str, int *elements)
{
	int		i;
	int		word_count;
	char	**array;

	i = 0;
	word_count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			get_through_quotes_and_count(str, &i, &word_count, '\"');
		else if (str[i] == '\'')
			get_through_quotes_and_count(str, &i, &word_count, '\'');
		else
			get_through_unquoted_and_count(str, &i, &word_count);
		if (str[i])
			i++;
	}
	*elements = word_count;
	array = alloc_array_and_words(data, str, word_count);
	return (array);
}
