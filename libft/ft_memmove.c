/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arybarsk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:28:23 by arybarsk          #+#    #+#             */
/*   Updated: 2023/09/13 19:38:47 by arybarsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *to, const void *from, size_t n)
{
	char		*t;
	const char	*f;
	size_t		i;

	t = (char *) to;
	f = (const char *) from;
	i = 0;
	if (t == f)
		return (to);
	if (t < f || t >= (f + n))
	{
		while (i < n)
		{
			t[i] = f[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i-- > 0)
			t[i] = f[i];
	}
	return (to);
}
