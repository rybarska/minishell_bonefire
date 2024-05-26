/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 20:51:55 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/19 20:53:22 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*newstring;

	i = 0;
	newstring = (char *)malloc(sizeof(char) * (ft_strlen((char *) s) + 1));
	if (!(newstring))
		return (NULL);
	while (s[i])
	{
		newstring[i] = f(i, s[i]);
		i++;
	}
	newstring[i] = '\0';
	return (newstring);
}
/*
#include <stdio.h>
int	main(void)
{
	char	*str = "come play with me";
	printf("%s\n", ft_strmapi(str, ft_toupper));
	return(0);
}
*/
