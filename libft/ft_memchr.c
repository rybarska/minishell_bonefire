/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 13:10:49 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/12 20:04:06 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*uc;

	uc = (unsigned char *) s;
	while (n > 0)
	{
		if (*uc == (unsigned char) c)
			return ((void *) uc);
		uc++;
		n--;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char string[] = "go try find something here";
	char is_in_memory = 'f';
	char not_in_memory = 'z';
	printf("%p\n", ft_memchr(string, is_in_memory, 20));
	printf("%p\n", ft_memchr(string, not_in_memory, 20));
} */
