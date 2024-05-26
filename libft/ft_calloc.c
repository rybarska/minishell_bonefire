/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 22:33:06 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 17:16:39 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;
	int		multiplied;

	multiplied = nmemb * size;
	if ((nmemb != 0 && size != 0) && multiplied / nmemb != size)
		return (NULL);
	space = malloc(nmemb * size);
	if (!space)
		return (NULL);
	ft_bzero(space, nmemb * size);
	return (space);
}
/*
#include <stdio.h>
int	main(void)
{
	int	*newspace;
	int i = 0;
	newspace = (int*)ft_calloc(10, sizeof(int));	
	while (i < 10)
	{
		newspace[i] = i;
		i++;
	}
	i = 0;
	while (i < 10)
	{
		printf("%d\n", newspace[i]);
		i++;
	}
	return (0);
} */
