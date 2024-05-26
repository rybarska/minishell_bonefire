/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 20:33:27 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 19:29:59 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_whitespace(const char *str)
{
	if (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		return (1);
	else
		return (0);
}

int	check_overflow(int sign_flag, long long number, const char *str)
{
	if (number > 214748364)
		return (-1);
	if (sign_flag == 1)
		if ((*str - '0') > (2147483647 - (number * 10)))
			return (-1);
	if (sign_flag == -1)
		if ((*str - '0') > -(-2147483648 + (number * 10)))
			return (-1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int				sign_flag;
	long long		number;

	sign_flag = 1;
	number = 0;
	while (*str && is_whitespace(str) > 0)
		str++;
	if ((*str == '+' || *str == '-') && *str++ == '-')
		sign_flag = -1;
	while ((*str >= '0') && (*str <= '9'))
	{
		if (check_overflow(sign_flag, number, str) != 0)
			return (-1);
		number = (number * 10) + (*str - '0');
		str++;
	}
	return (number * sign_flag);
}
/*
#include<stdio.h>
int	main(void)
{
	char	numstring[] = {"  \v  ---+--+2147483648ab5676"};
	printf("%d\n", ft_atoi(numstring));
} */
