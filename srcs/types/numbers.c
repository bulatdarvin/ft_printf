/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:10:03 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:10:05 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"
int		type_u(va_list arg, t_flags *flag)
{
	return(help_to_base(arg, flag, 10, NULL));
}

int		type_x(va_list arg, t_flags *flag)
{
	return(help_to_base(arg, flag, 16, "0x"));
}

int		type_x_upper(va_list arg, t_flags *flag)
{
	return(help_to_base(arg, flag, 16, "0X"));
}

int		type_o(va_list arg, t_flags *flag)
{
	return(help_to_base(arg, flag, 8, "0"));
}

int		write_d(char *a, int size, int precision, t_flags *flag, intmax_t nb)
{
	int width;
	int pre_width;

	pre_width = 0;
	width = 0;
	if (!flag->minus)
	{
		if (flag->width && flag->zero)
			sign(nb, flag);
		width = ft_width(size, flag);
	}
	if ((flag->width && (flag->minus || !flag->zero)) || !flag->width)
		sign(nb, flag);
	while (pre_width++ < precision)
		ft_write("0", 1, flag);
	if (size > 0)
		ft_write(a, ft_strlen(a), flag);
	return (width + size);
}

int     type_d(va_list arg, t_flags *flag)
{
    int size;
    intmax_t nb;
	char *a;
	int precision;

	nb = ft_get_nb(arg, *flag);
	a = ft_itoa(FT_ABS(nb));
	if (flag->precision != 0)
		flag->zero = 0;
	precision = flag->precision - ft_strlen(a);
	size = (flag->precision > (int)ft_strlen(a)) ? flag->precision : ft_strlen(a);
	size = (flag->precision == -1 && nb == 0) ? 0 : size;
	size += ((nb >= 0 && (flag->plus || flag->space)) || nb < 0) ? 1 : 0;

    size = write_d(a, size, precision, flag, nb);
	size = (flag->minus) ? ft_width(size, flag) : size;
    return (size);
}

char	*ft_strlow(char *a)
{
	int i;

	i = 0;
	while (i < ft_strlen(a))
		a[i] = ft_tolower(a[i++]);
	return (a);
}

void	pad(char *a, t_flags *flag, char *hash_key, int size, int nb)
{
	int width;
	int precision;

	if (flag->precision <= 0 && flag->width <= 0)
		return ;
	precision = flag->precision - ft_strlen(a);
	precision = (flag->precision > ft_strlen(a)) ? precision : 0;
	size = (flag->precision == -1) ? size : size + precision;
	width = 0;
	while (flag->minus && width++ < precision)
		ft_write("0", 1, flag);
	if (flag->minus && (flag->precision != -1 || nb != 0))
		ft_write(a, ft_strlen(a), flag);
	width = 0;
	ft_width(size, flag);
	while (!flag->minus && width++ < precision)
		ft_write("0", 1, flag);
}

int		help_to_base(va_list arg, t_flags *flag, int base, char *hash_key)
{
	int size;
	intmax_t nb;
	char *a;

	if (hash_key)
		nb = ft_get_nb(arg, *flag);
	else
		nb = ft_get_nb_u(arg, *flag);
	a = ft_itoa_base(nb, base);
	if (flag->type == 'x')
		a = ft_strlow(a);
	if (flag->hash && (nb != 0 || (flag->precision == -1 && ft_strequ(hash_key, "0"))) && (flag->minus || !flag->width || flag->zero))
		ft_write(hash_key, ft_strlen(hash_key), flag);
	flag->width = (nb == 0) ? flag->width + 1 : flag->width; 
	size = (flag->hash) ? (ft_strlen(a) + ft_strlen(hash_key)) : ft_strlen(a);
//	ft_putnbr(size);
//	ft_putchar('\n');
	pad(a, flag, hash_key, size, nb);
	if (flag->hash && !flag->minus && flag->width && nb != 0 && !flag->zero)
		ft_write(hash_key, ft_strlen(hash_key), flag);
	if (!flag->minus && flag->precision != -1)
		ft_write(a, ft_strlen(a), flag);
	return(ft_strlen(a));
}

