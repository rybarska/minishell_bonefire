/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:07:43 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/09 14:28:26 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	concat;
	unsigned int	destlen;
	unsigned int	srclen;

	if (dest == NULL || src == NULL)
		return (0);
	concat = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	if (size <= destlen)
		return (size + srclen);
	while (src[concat] != '\0' && size - 1 > destlen + concat)
	{
		dest[destlen + concat] = src[concat];
		concat++;
	}
	dest[destlen + concat] = '\0';
	return (destlen + srclen);
}
/*
int	main(void)
{
	char	dest[11] = "append";
	char	src[] = "myfriend";
	int	size = 15;
	
	printf("%u\n", ft_strlcat(dest, src, size));
	printf("%s\n", dest);
	return (0);
} */
