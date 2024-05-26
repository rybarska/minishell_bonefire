/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:24:20 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/09 14:21:27 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	unsigned char	*uc;

	uc = (unsigned char *) str;
	while (n > 0)
	{
		*uc = (unsigned char) c;
		uc++;
		n--;
	}
	return (str);
}
/*
#include <string.h>
#include <stdio.h>
int	main(void)
{
	char	string[] = "go change this";
	printf("%s\n", string);
	memset(string, 70, 6);
	printf("%s\n", string);
	ft_memset(string, 72, 12);
	printf("%s\n", string);
	return (0);
}*/
