#include "fdf.h"

int	chars(int fd, int i, char *argc)
{
	char	b;

	i = 0;
	fd = open(argc, O_RDONLY);
	if (fd < 0)
	{
		write(1, "error\n", 6);
		exit(1);
	}
	while (read(fd, &b, 1))
		i++;
	close(fd);
	return (i);
}

char	*buffer(int fd, int i, char *argc, char *buf)
{	
	char	b;

	i = 0;
	fd = open(argc, O_RDONLY);
	while (read(fd, &b, 1))
		buf[i++] = b;
	close(fd);
	return (buf);
}

t_fdf	map(char *buf, int i, int fd, t_fdf *field)
{
	i = 0;
	fd = 1;
	while (buf[i] != '\n')
	{
		i++;
		if (buf[i] == ' ')
		{
			while (buf[i + 1] == ' ')
				i++;
			field->width++;
		}
	}
	i = 0;
	while (buf[i + 1])
	{
		if (buf[i] == '\n')
		{
			field->hight++;
			fd = 1;
		}
		i++;
	}
}

int	**full_map(char *buf, int fd, t_fdf field)
{
	int	i;
	int	count;

	i = 0;
	fd = 0;
	count = 0;
	while (field.hight != i)
	{
		del_pointer(&field, i);
		field.matrix[i][count] = ft_atoi(&buf[fd]);
		count++;
		while (buf[fd] != '\n' && buf[fd])
		{
			if (buf[fd] == ' ')
			{
				while (buf[fd + 1] == ' ')
					fd++;
				field.matrix[i][count] = ft_atoi(&buf[fd + 1]);
				count++;
			}
			fd++;
		}
		counter(&i, &count, &fd);
	}
	return (field.matrix);
}

t_fdf	main_reader(char *argc)
{
	int		fd;
	int		i;
	char	*buf;
	t_fdf	field;

	field.width = 1;
	field.hight = 1;
	buf = (char *)malloc(sizeof(char) * chars(fd, i, argc));
	if (!buf)
	{
		free(buf);
		exit(1);
	}
	buf = buffer(fd, i, argc, buf);
	map (buf, i, fd, &field);
	field.matrix = (int **)malloc(sizeof(int *) * field.hight);
	if (!field.matrix)
	{
		free(field.matrix);
		free(buf);
		exit(1);
	}
	field.matrix = full_map(buf, fd, field);
	free(buf);
	return (field);
}
