/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 13:42:16 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 19:27:56 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*new_string;
	unsigned int	i;
	unsigned int	s_len;

	i = start;
	s_len = ft_strlen((char *) s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	new_string = malloc(sizeof(char) * (len + 1));
	if (new_string == NULL)
		return (NULL);
	while (s[i] && len > 0)
	{
		new_string[i - start] = s[i];
		len--;
		i++;
	}
	new_string[i - start] = '\0';
	return (new_string);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_substr("go create a substring", 3, 6));
	printf("%s\n", ft_substr("go create a substring", 10, 30));
	return (0);
}*/
