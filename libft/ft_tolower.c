/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 21:04:11 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/20 13:15:08 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
/*
#include <stdio.h>
int	main(void)
{
	printf("%c\n", ft_tolower('R'));
	printf("%c\n", ft_tolower('p'));
	printf("%c\n", ft_tolower('*'));
	printf("%c\n", ft_tolower('\200'));
	return (0);
}*/
