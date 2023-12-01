/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:02:13 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/30 10:10:05 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check(int fd, char *buffer)
{
	if (fd < 0 || fd > 512 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		*buffer = 0;
		return (1);
	}
	return (0);
}

static char	*clean(char *next_line)
{
	if (next_line)
	{
		if (*next_line)
			return (next_line);
		free(next_line);
	}
	return (NULL);
}

static char	*concatenate(char *heap_str, char *buf_str, int len)
{
	int		index;
	char	*new_str;

	index = 0;
	new_str = malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (heap_str && *heap_str)
	{
		new_str[index] = heap_str[index];
		index++;
	}
	while (buf_str && *buf_str && index < len)
	{
		new_str[index] = *buf_str;
		index++;
		buf_str++;
	}
	new_str[index] = 0;
	if (heap_str)
	{
		free(heap_str);
	}
	return (new_str);
}

static char	*form_nl(char *next_line, char *buffer, char *newline)
{
	int		len;
	char	*new_string;

	len = 0;
	if (next_line)
		len += ft_strlen(next_line);
	len += ft_strlen(buffer);
	if (newline)
		len -= ft_strlen(newline + 1);
	if (newline)
	{
		new_string = concatenate(next_line, buffer, len);
		buffer = ft_memcpy(buffer, newline + 1, ft_strlen(newline + 1) + 1);
		return (clean(new_string));
	}
	new_string = concatenate(next_line, buffer, len);
	*buffer = 0;
	return (new_string);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			bytes_read;
	char		*newline;

	if (check(fd, buffer))
		return (NULL);
	next_line = NULL;
	while ("there is stuff to read and no newline characters found")
	{
		if (!*buffer)
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read < 0)
				return (clean(NULL));
			if (bytes_read == 0)
				return (clean(next_line));
			buffer[bytes_read] = 0;
		}
		newline = ft_strchr(buffer, '\n');
		if (newline)
			return (form_nl(next_line, buffer, newline));
		next_line = form_nl(next_line, buffer, newline);
		if (!next_line)
			return (clean(next_line));
	}
}
