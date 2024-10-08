/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhuszar <mhuszar@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:33:17 by arybarsk          #+#    #+#             */
/*   Updated: 2024/06/22 17:06:40 by mhuszar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *str, char c)
{
	size_t	len;
	char	*joined_string;

	len = ft_strlen((char *) str);
	joined_string = malloc(sizeof(char) * (len + 2));
	if (joined_string == NULL)
		return (NULL);
	ft_strlcpy(joined_string, (char *) str, len + 1);
	joined_string[len] = c;
	joined_string[len + 1] = '\0';
	return (joined_string);
}

char	*ft_strjoin_free(char *str, char c)
{
	size_t	len;
	char	*joined_string;

	len = ft_strlen((char *) str);
	joined_string = malloc(sizeof(char) * (len + 2));
	if (joined_string == NULL)
		return (NULL);
	ft_strlcpy(joined_string, (char *) str, len + 1);
	joined_string[len] = c;
	joined_string[len + 1] = '\0';
	free(str);
	return (joined_string);
}
