#include "includes/struct.h"
#include <stdio.h>

char	*ft_strlow(char *a)
{
	int i;

	i = 0;
	while (i < ft_strlen(a))
  {
		ft_tolower(a[i++]);
    ft_putchar(a[i - 1] + 32);
    ft_putchar('\n');
  }
  ft_putnbr(i);
	return (a);
}

int main()
{
  char *a = "ABC";
  ft_putendl(ft_strlow(a));
  //printf("%.5s\n","1234567");
  return (0);
}
