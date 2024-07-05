/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:55:14 by arybarsk          #+#    #+#             */
/*   Updated: 2024/07/05 11:26:29 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		s1_size;
	int		s2_size;
	char	*joined_string;

	i = 0;
	s1_size = ft_strlen((char *) s1);
	s2_size = ft_strlen((char *) s2);
	joined_string = malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (joined_string == NULL)
		return (NULL);
	while (i < s1_size)
	{
		joined_string[i] = s1[i];
		i++;
	}
	while (i < (s1_size + s2_size))
	{
		joined_string[i] = s2[i - s1_size];
		i++;
	}
	joined_string[i] = '\0';
	return (joined_string);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%s\n", ft_strjoin("join", " these"));
}
*/
