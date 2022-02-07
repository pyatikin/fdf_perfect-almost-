#include "fdf.h"

static int	wht_zero(int n, int sign)
{
	if (sign == 0 && n < 0)
		return (-1);
	if (sign == -1 && n > 0)
		return (0);
	return (n);
}

int	ft_atoi(const char *s)
{
	int	sign;
	int	num;

	sign = 0;
	num = 0;
	while (*s == 32 || (*s >= 9 && *s <= 13))
		s++;
	if (*s == 45)
	{
		sign = -1;
		s++;
	}
	else if (*s == 43)
		s++;
	while (*s >= 48 && *s <= 57)
		num = 10 * num + *(s++) - 48;
	if (sign == -1)
		num = -num;
	if (wht_zero(num, sign) == -1 || wht_zero(num, sign) == 0)
		return (wht_zero(num, sign));
	return (num);
}

int	difference(t_fdf field)
{
	int	min;
	int	max;
	int	i;
	int	j;

	i = 0;
	j = 0;
	min = 2147483647;
	max = -2147483647;
	while (j < field.hight)
	{
		i = 0;
		while (i < field.width)
		{
			if (field.matrix[j][i] > max)
				max = field.matrix[j][i];
			if (field.matrix[j][i] < min)
				min = field.matrix[j][i];
			i++;
		}
		j++;
	}
	if ((max - min) == 0)
		return (1);
	return (max - min);
}

void	del_pointer(t_fdf *field, int i)
{
	int	del;

	del = 0;
	field->matrix[i] = (int *)malloc(sizeof(int) * field->width);
	if (!field->matrix[i])
	{
		while (del <= i)
			free(field->matrix[del++]);
		exit(1);
	}
}

void	counter(int *i, int *count, int *fd)
{
	*count = 0;
	(*fd)++;
	(*i)++;
}
