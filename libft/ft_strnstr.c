/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:19:06 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 19:42:44 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*cast_big;
	char	*cast_little;
	size_t	little_len;

	cast_big = (char *) big;
	cast_little = (char *) little;
	little_len = ft_strlen(cast_little);
	if (little_len == 0)
		return ((char *) cast_big);
	while (*cast_big && len >= little_len)
	{
		if (ft_strncmp(cast_big, cast_little, little_len) == 0)
			return ((char *) cast_big);
		cast_big++;
		len--;
	}
	return (NULL);
}
/*
#include <stdio.h>
int	main(void)
{
	char	hay[] = "we need to find the needle here";
	char	needle[] = "need";
	printf("%s\n", ft_strnstr(hay, needle, 30));
	return (0);
} */
