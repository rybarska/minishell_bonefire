/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 20:57:07 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/09 14:17:54 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*uc;

	uc = (unsigned char *) str;
	while (n > 0)
	{
		*uc = '\0';
		uc++;
		n--;
	}
}
/*
#include <stdio.h>
int	main(void)
{
	char string[] = "go zero this";
	ft_bzero(string, 8);
	printf("%s\n", string);
}*/
