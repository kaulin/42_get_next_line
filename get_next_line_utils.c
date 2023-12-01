/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:56:53 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/30 13:00:52 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(char *s, int c)
{
	while (*s)
	{
		if ((unsigned char)*s == (unsigned char)c)
			return (s);
		s++;
	}
	if ((unsigned char)*s == (unsigned char)c)
		return (s);
	return (NULL);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*to;
	unsigned char	*from;
	size_t			i;

	to = (unsigned char *)dst;
	from = (unsigned char *)src;
	i = 0;
	if (src == dst)
		return (dst);
	while (i < n)
	{
		to[i] = from[i];
		i++;
	}
	return (dst);
}

// Frees one argument pointer also resetting it to null, and returns the other
char	*clean(char *waste_pointer, char *return_pointer)
{
	if (waste_pointer)
	{
		free(waste_pointer);
		waste_pointer = NULL;
	}
	return (return_pointer);
}
