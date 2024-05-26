/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:40:25 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/24 17:40:27 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strdup_array(char **src_array)
{
	int		i;
	char	**dest_array;

	i = 0;
	while (src_array[i])
		i++;
	dest_array = (char **)malloc(sizeof(char *) * (i + 1));
	if (!dest_array)
		return (NULL);
	i = 0;
	while (src_array[i])
	{
		dest_array[i] = ft_strdup(src_array[i]);
		if (!dest_array[i])
		{
			ft_free_array(dest_array);
			return (NULL);
		}
		i++;
	}
	dest_array[i] = NULL;
	return (dest_array);
}
