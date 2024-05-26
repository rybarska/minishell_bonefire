/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 19:55:37 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/19 18:38:35 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed_string;
	int		start;
	int		end;
	int		i;

	if (!s1)
		return (NULL);
	start = 0;
	end = ft_strlen((char *) s1);
	i = 0;
	while (start < end && ft_strchr(set, s1[start]))
		start++;
	while (end - 1 > start && ft_strrchr(set, s1[end - 1]))
		end--;
	if (end <= start)
		return (ft_strdup(""));
	trimmed_string = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!(trimmed_string))
		return (NULL);
	while (i++ < start)
		s1++;
	ft_strlcpy(trimmed_string, (char *)s1, end - start + 1);
	return (trimmed_string);
}
/*
int	main(void)
{
	printf("%s\n", ft_strtrim("trimgjkgjkgjkjgkjthis", "this trim"));
	return (0);
} */
