#include "includes/struct.h"
#include <stdio.h>

# define VERY -9223372036854775808UL
static void		zap(char *a, intmax_t n, int size)
{
	int tmp;

	if (n == 0)
		a[0] = '0';
	while (size > 0 && n != 0)
	{
		if ((uintmax_t)n == VERY)
			tmp = 8;
		else
			tmp = ABS(n % 10);
		a[size - 1] = tmp + '0';
		n = n / 10;
		size--;
	}
}

static	char	*sozd(int min, int size, intmax_t n)
{
	char *a;

	if (min == -1 && (uintmax_t)n != VERY)
	{
		if (!(a = ft_strnew(size + 1)))
			return (NULL);
		a[0] = '-';
		zap(a, n, size + 1);
	}
	else
	{
		a = ft_strnew(size);
		if (a == 0)
			return (NULL);
		zap(a, n, size);
	}
	return (a);
}

char			*func(intmax_t n)
{
	intmax_t	num;
	int			size;
	int			min;
	char		*a;

	min = 1;
	size = 1;
	num = n;
	if (n < 0)
	{
		num = num * (-1);
		min = -1;
	}
	while (n / 10 != 0)
	{
		size++;
		n = n / 10;
	}
	a = sozd(min, size, num);
	if (a == 0)
		return (NULL);
	return (a);
}

int main()
{
ft_printf("%03.2d\n", 1);
	return (0);
}
