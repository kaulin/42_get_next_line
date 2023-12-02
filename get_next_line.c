/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line_recursive.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 09:46:08 by jajuntti          #+#    #+#             */
/*   Updated: 2023/11/29 12:31:57 by jajuntti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_params(int fd, char *buffer)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		return (1);
	}
	return (0);
}

static int	calculate_merged_length(char *line, char *buffer, char *line_end)
{
	int		len;

	len = 0;
	if (line)
		len += ft_strlen(line);
	len += ft_strlen(buffer);
	if (line_end)
		len -= ft_strlen(line_end + 1);
	return (len);
}

static char	*merge(char *line, char *buffer, char *line_end)
{
	int		old_len;
	int		new_len;
	char	*new_str;

	old_len = 0;
	new_len = calculate_merged_length(line, buffer, line_end);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (clean(line, NULL));
	if (line && *line)
	{
		old_len = ft_strlen(line);
		ft_memcpy(new_str, line, ft_strlen(line));
	}
	if (buffer && *buffer)
		ft_memcpy(new_str + old_len, buffer, new_len - old_len);
	new_str[new_len] = 0;
	if (!line_end)
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
	return (clean(line, new_str));
}

static int	read_buffer(int fd, char *buffer, int *file_end)
{
	int	bytes_read;

	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0 || buffer == NULL)
	{
		ft_memset(buffer, 0, BUFFER_SIZE + 1);
		return (1);
	}
	if (bytes_read < BUFFER_SIZE)
		*file_end = 1;
	buffer[bytes_read] = 0;
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			file_end;
	char		*line_end;

	line = NULL;
	file_end = 0;
	if (check_params(fd, buffer))
		return (NULL);
	while ("There is stuff to do")
	{
		if (*buffer == 0)
			if (read_buffer(fd, buffer, &file_end) || (!line && *buffer == 0))
				return (clean(line, NULL));
		line_end = ft_strchr(buffer, '\n');
		line = merge(line, buffer, line_end);
		if (line_end)
			ft_memcpy(buffer, line_end + 1, ft_strlen(line_end + 1) + 1);
		if (!line || line_end || file_end)
			return (line);
	}
}
