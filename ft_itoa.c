#include "fdf.h"

static int	numlen(long long n)
{
	size_t	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	putnumb(long n, char *str, int i)
{
	int	size;

	size = numlen(n) + i;
	while (n > 9)
	{
		str[--size] = (n % 10) + 48;
		n = n / 10;
	}
	str[i] = n + 48;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	long	num;

	i = 0;
	num = n;
	str = malloc(numlen(num) + 1);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[i++] = 45;
		num *= -1;
		str[numlen(num) + 1] = '\0';
	}
	else
		str[numlen(num)] = '\0';
	putnumb(num, str, i);
	return (str);
}
