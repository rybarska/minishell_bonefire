/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:14:18 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/09 14:28:43 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	length;

	i = 0;
	length = ft_strlen(src);
	if (size != 0)
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (length);
}
/* 
#include<unistd.h>
#include<stdio.h>

int     main(void)
{
        char    dest[] = {"change this beginning"};
        char    src[] = {"have a new"};
	unsigned int	size = 11;
       	printf("%d\n",ft_strlcpy(dest, src, size));
	write(1, dest, 21);
} */
