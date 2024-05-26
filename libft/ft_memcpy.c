/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:43:43 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/19 16:42:33 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *to, const void *from, size_t n)
{
	int		i;
	char	*t;
	char	*f;

	if (!to && !from && n > 0)
		return (NULL);
	i = 0;
	t = (char *) to;
	f = (char *) from;
	while (n > 0)
	{
		t[i] = f[i];
		i++;
		n--;
	}
	return (to);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char str1[] = "to here you copy";
	char str2[] = "from here you take";
	char str3[] = "now take this instead";
	memcpy(str1, str2, sizeof(str2));
	printf("%s\n", str1);
	ft_memcpy(str1, str3, sizeof(str3));
	printf("%s\n", str1);
	return (0);
} */
