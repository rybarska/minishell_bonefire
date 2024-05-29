/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:54:21 by arybarsk          #+#    #+#             */
/*   Updated: 2024/05/24 17:54:23 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
		{
			free(array[i]);
			array[i] = NULL;
		}
		free(array);
		array = NULL;
	}
}
