/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_split_returns.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 21:47:37 by mhuszar           #+#    #+#             */
/*   Updated: 2024/06/21 13:05:50 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr_prot(t_data *data, char *s, int start, int len)
{
	char	*new_string;
	int		i;
	int		s_len;

	i = start;
	s_len = ft_strlen((char *)s);
	// if (start >= s_len) //will this ever happen?
	// 	return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (new_string == NULL)
		snuff_it(data, "Error: malloc failed at substr_protect\n", NULL, 255);
	while (s[i] && len > 0)
	{
		new_string[i - start] = s[i];
		len--;
		i++;
	}
	new_string[i - start] = '\0';
	return (new_string);
}

int	count_words_q(t_data *data, char *str, int *elements)
{
	int		words;
	bool	flag;

	data->is_s_quoted = 0;
	words = 0;
	flag = false;
	if (!str)
		return (words);
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && !data->is_s_quoted)
			data->is_s_quoted = *str;
		else if (*str == '\'' || *str == '\"')
			data->is_s_quoted = 0;
		if (*str == ' ' && !data->is_s_quoted)
			flag = false;
		else if (flag == false)
		{
			words++;
			flag = true;
		}
		str++;
	}
	*elements = words;
	return (words);
}

void	init_vals(int *start, int *end, int *ctr, bool *flag)
{
	*end = -1;
	*ctr = 0;
	*flag = false;
	*start = 0;
}

char	**malloc_for_res(t_data *data, int size)
{
	char	**result;

	data->is_s_quoted = 0;
	result = malloc(sizeof(char *) * (size + 1));
	if (!result)
		snuff_it(data, "Error: malloc failed at split special\n", NULL, 255);
	return (result);
}

char	**ft_split_returns(t_data *data, char *str, int *elements)
{
	int		start;
	int		end;
	int		counter;
	char	**result;
	bool	flag;

	init_vals(&start, &end, &counter, &flag);
	result = malloc_for_res(data, count_words_q(data, str, elements));
	while (str[start])
	{
		if (str[++end] == data->is_s_quoted && data->is_s_quoted)
			data->is_s_quoted = 0;
		else if ((str[end] == '\'' || str[end] == '\"') && !data->is_s_quoted)
			data->is_s_quoted = str[end];
		if ((((str[end] == ' ' && !data->is_s_quoted) || !str[end])) && flag)
		{
			result[counter++] = ft_substr_prot(data, str, start, end - start);
			start = end + (str[end] != '\0');
			flag = false;
		}
		start += (flag == 0 && str[start] == ' ');
		flag = (str[end] != ' ' && !data->is_s_quoted);
	}
	result[counter] = NULL;
	return (result);
}
