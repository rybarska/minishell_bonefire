/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 22:21:55 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 19:43:44 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last_c;

	last_c = NULL;
	while (*s)
	{
		if (*s == (unsigned char) c)
			last_c = s;
		s++;
	}
	if (*s == (unsigned char) c)
		last_c = s;
	if (last_c != NULL)
		return ((char *) last_c);
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	hay[] = "go find the needle here";
	char	needle_present = 'n';
	char	needle_absent = '3';
	printf("%p\n", (void *)ft_strrchr(hay, needle_present));
	printf("%p\n", (void *)ft_strrchr(hay, needle_absent));
	return (0);
} */
