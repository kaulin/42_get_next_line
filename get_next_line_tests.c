#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

/*
static int	error(char *error)
{
	puts(error);
	return (1);
}

static void	put_file(int fd)
{
	char *next_line;

	next_line = get_next_line(fd);
	while (next_line)
	{
		printf("%s", next_line);
		free(next_line);
		next_line = get_next_line(fd);
	}
	puts("");
}
*/

static int	*clean_array(int *array)
{
	free(array);
	return (NULL);
}

static void	put_files(int *fd_array)
{
	int		index;
	char	*next_line;
	int		line_counter;
	int		printed;

	index = 0;
	printed = 1;
	line_counter = 1;
	while (printed)
	{
		printed = 0;
		while (fd_array[index] > 0)
		{
			next_line = get_next_line(fd_array[index]);
			if (next_line)
			{
				printf("FD-%d, line %d = %s", fd_array[index], line_counter, next_line);
				printed = 1;
			}
			else
				close(fd_array[index]);
			free(next_line);
			next_line = NULL;
			index++;
		}
		puts("");
		line_counter++;
		index = 0;
	}
}

static int *open_files(int argc, char *argv[])
{
	int	index;
	int	*fd_array;

	index = 1;
	fd_array = malloc(argc * sizeof(int));
	if (!fd_array)
		return (NULL);
	while (index < argc)
	{
		fd_array[index - 1] = open(argv[index], O_RDONLY);
		if (fd_array[index - 1] < 0)
		{
			printf("Error opening file '%s'\n", argv[index]);
			return (clean_array(fd_array));
		}
		index++;
	}
	fd_array[index] = -1;
	return (fd_array);
}

int	main(int argc, char *argv[])
{
	int		*fd_array;
	int		index;

	index = 1;
	if (argc < 2)
	{
		puts("Need at least one filepath");
		return (0);
	}
	fd_array = open_files(argc, argv);
	if (!fd_array)
		return (1);
	put_files(fd_array);
	clean_array(fd_array);
	return (0);
}
