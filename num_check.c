/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 15:37:27 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/18 15:37:29 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_overflow(char *numstr)
{
	int	result;
	int	digit;
	int	sign;

	result = 0;
	sign = 1;
	if (!numstr || *numstr == '\0')
		return (1);
	if (numstr[0] == '-')
		sign = -1;
	if (*numstr == '+' || *numstr == '-')
		numstr++;
	while (*numstr != '\0')
	{
		digit = *numstr - '0';
		if ((sign == 1) && ((result > MAX_INT / 10)
				|| (result >= MAX_INT / 10 && digit > MAX_INT % 10)))
			return (1);
		else if ((sign == -1) && ((result < MIN_INT / 10)
				|| (result <= MIN_INT / 10 && digit > -(MIN_INT % 10))))
			return (1);
		result = result * 10 + sign * digit;
		numstr++;
	}
	return (0);
}

static int	is_not_numeric(char *numstr)
{
	int	sign;
	int	i;

	sign = 1;
	i = 0;
	while (numstr[i] && ft_iswhitespace(numstr[i]))
		++i;
	if (numstr[i] == '\0')
		return (1);
	if (numstr[i] == '-' || numstr[i] == '+')
	{
		if (numstr[i] == '-')
			sign = -1;
		i++;
	}
	if (!(numstr[i] >= '0' && numstr[i] <= '9'))
		return (1);
	while (numstr[i] == '0')
		i++;
	while (numstr[i] >= '0' && numstr[i] <= '9')
		i++;
	if (numstr[i] != '\0')
		return (1);
	return (0);
}

int	get_input_num(char *numstr)
{
	int	num;

	num = 0;
	if (numstr == NULL || *numstr == '\0' || is_not_numeric(numstr))
		return (-264);
	if (is_overflow(numstr))
		return (-2);
	num = ft_atoi(numstr);
	return (num);
}
