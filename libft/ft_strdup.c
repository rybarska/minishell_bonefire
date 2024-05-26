/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 15:00:15 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/11 13:12:39 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		s_size;
	char	*pass_string;
	char	*new_string;
	char	*new_string_start;

	pass_string = (char *) s;
	s_size = ft_strlen(pass_string);
	new_string = (char *)malloc(s_size + 1);
	if (new_string == NULL)
		return (NULL);
	new_string_start = new_string;
	while (*s)
	{
		*new_string = *s;
		new_string++;
		s++;
	}
	*new_string = '\0';
	return (new_string_start);
}
/*
#include <stdio.h>
int	main(void)
{
	ft_strdup("go duplicate this");
}*/
