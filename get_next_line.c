/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:02:13 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/27 17:41:48 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check(int fd, char *buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		buffer[0] = 0;
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
		next_line = NULL;
	}
	return (NULL);
}

static char	*concatenate(char *new_str, char *heap_str, char *buf_str)
{
	int		index;

	index = 0;
	while (heap_str && *heap_str)
	{
		new_str[index] = heap_str[index];
		index++;
	}
	while (buf_str && *buf_str)
	{
		new_str[index] = *buf_str;
		index++;
		buf_str++;
	}
	new_str[index] = 0;
	if (heap_str)
	{
		free(heap_str);
		heap_str = NULL;
	}
	return (new_str);
}

static char	*form_nl(char *next_line, char *buffer, char *end_of_line)
{
	char	*new_string;
	int		len;

	len = 0;
	if (end_of_line)
		*(end_of_line + 1) = 0;
	if (next_line)
		len += ft_strlen(next_line);
	len += ft_strlen(buffer);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	return (concatenate(new_string, next_line, buffer));
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*next_line;
	int			bytes_read;
	char		*end_of_line;

	if (check(fd, buffer))
		return (NULL);
	next_line = NULL;
	while ("there is stuff to read and no newline characters found")
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (clean(next_line));
		buffer[bytes_read] = 0;
		end_of_line = ft_strchr(buffer, '\n');
		if (end_of_line)
			return (clean(form_nl(next_line, buffer, end_of_line)));
		next_line = form_nl(next_line, buffer, end_of_line);
		if (!next_line)
			return (clean(next_line));
	}
	return (next_line);
}
