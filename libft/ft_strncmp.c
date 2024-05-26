/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:29:21 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/19 16:47:31 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	if (n == 0)
		return (0);
	while ((*s1 || *s2) && i < n)
	{
		if ((unsigned char) *s1 != (unsigned char) *s2)
			return ((unsigned char) *s1 - (unsigned char) *s2);
		i++;
		s1++;
		s2++;
	}
	return (0);
}
/*
#include<stdio.h>
#include <string.h>
#include <limits.h>
int	main(void)
{
	char	*string1;
	char	*string2;
	int		length;
	
	string1 = "abcdef";
	string2 = "abc\375xx";
	length = 50;
	printf("strncmp = %d\n", strncmp(string1, string2, length));
	printf("ft_strncmp = %d\n", ft_strncmp(string1, string2, length));
}
*/
