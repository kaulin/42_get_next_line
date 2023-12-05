#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

static int	error(char *error)
{
	puts(error);
	return (1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*next_line;	

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (error("Error opening file"));

	if (close(fd))
		return (error("Error closing file"));
	return (0);
}
