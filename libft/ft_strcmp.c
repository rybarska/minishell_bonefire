/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 17:28:14 by arybarsk          #+#    #+#             */
/*   Updated: 2023/05/04 17:15:26 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	long	i;
	int		result;

	i = 0;
	while ((s1[i] != '\0' && s2[i]) != '\0')
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	result = s1[i] - s2[i];
	return (result);
}
/* 
#include<stdio.h>
int	main(void)
{
	char string1[] = {"compare me"};
	char string2[] = {"compare you to what?"};
	printf("%d\n", ft_strcmp(string1, string2));
} */
