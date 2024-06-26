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

char	**ft_split_bonefire(t_data *data, char *str, int *elements)
{
	int	i = 0;
	int	j = 0;
	int	k = 0;
	int	wc = 0;
	char	**out;

	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
			if (str[i] == '\"')
				i++;
			wc++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (str[i] == '\'')
				i++;
			wc++;
		}
		else
		{
			while (str[i] && ft_iswhitespace(str[i]))
				i++;
			if (str[i] && str[i] != '\"' && str[i] != '\'')
				wc++;
			while (str[i] && str[i] != '\"' && str[i] != '\'' && !ft_iswhitespace(str[i]))
				i++;
		}
		if (str[i])
			i++;
	}
	*elements = wc;
	out = (char **)malloc(sizeof(char *) * (wc + 1));
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		else if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		else
		{
			while (str[i] && ft_iswhitespace(str[i]))
				i++;
			j = i;
			while (str[i] && str[i] != '\"' && str[i] != '\'' && !ft_iswhitespace(str[i]))
				i++;
		}
		if ((str[i] == '\0' || ft_iswhitespace(str[i])) && i > j)
		{
			out[k] = (char *)malloc(sizeof(char) * ((i - j) + 1));
			if (!out[k])
				snuff_it(data, "Error allocating memory \n", NULL, 255);
			ft_strncpy(out[k++], &str[j], i - j);
			j = i;
		}
	}
	out[k] = NULL;
	return (out);
}
