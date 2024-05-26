/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:07:03 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/12 20:06:31 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*uc1;
	const unsigned char	*uc2;

	uc1 = (unsigned char *) s1;
	uc2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (*uc1 != *uc2)
			return (*uc1 - *uc2);
		uc1++;
		uc2++;
		n--;
	}
	return (0);
}
/*
#include <stdio.h>
int	main(void)
{
	char str1[] = "compare";
	char str2[] = "comparE";
	printf("%d\n", ft_memcmp(str1, str2, 5));
	printf("%d\n", ft_memcmp(str1, str2, 7));
} */
