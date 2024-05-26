/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 19:55:33 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/24 19:55:35 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_join(char **src_array, char *string)
{
	int		i;
	char	**dest_array;

	i = 0;
	while (src_array[i])
		i++;
	dest_array = (char **)malloc(sizeof(char *) * (i + 2));
	if (!dest_array)
		return (NULL);
	i = 0;
	while (src_array[i])
	{
		dest_array[i] = ft_strdup(src_array[i]);
		if (!dest_array[i])
			return (ft_free_array(dest_array), NULL);
		i++;
	}
	dest_array[i] = ft_strdup(string);
	if (!dest_array[i])
		return (ft_free_array(dest_array), NULL);
	dest_array[i + 1] = NULL;
	return (dest_array);
}
