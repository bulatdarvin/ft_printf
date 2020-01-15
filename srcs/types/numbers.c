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
	return (help_to_base(arg, flag, 10, NULL));
}

int		type_x(va_list arg, t_flags *flag)
{
	return (help_to_base(arg, flag, 16, "0x"));
}

int		type_x_upper(va_list arg, t_flags *flag)
{
	return (help_to_base(arg, flag, 16, "0X"));
}

int		type_o(va_list arg, t_flags *flag)
{
	return (help_to_base(arg, flag, 8, "0"));
}

int		type_b(va_list arg, t_flags *flag)
{
	return (help_to_base(arg, flag, 2, "0"));
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
	free(a);
    return (size);
}

char	*ft_strlow(char *a)
{
	int i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] <= 'Z' && a[i] >= 'A')
			a[i] = a[i] + 32;
		i++;
	}
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
	precision -= ((!flag->width && flag->hash && nb != 0 && flag->type == 'o') ? ft_strlen(hash_key) : 0);
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

int		help_to_base(va_list arg, t_flags *flag, uintmax_t base, char *hash_key)
{
	int size;
	uintmax_t nb;
	char *a;

	nb = ft_get_nb_u(arg, *flag);
	a = ft_itoa_base(nb, base);
	if (flag->type == 'x')
		a = ft_strlow(a);
	if (flag->hash && (nb != 0 || (flag->precision == -1 && ft_strequ(hash_key, "0"))) && (flag->minus || !flag->width || flag->zero))
		ft_write(hash_key, ft_strlen(hash_key), flag);
	flag->width = (nb == 0) ? flag->width + 1 : flag->width; 
	size = (flag->hash) ? (ft_strlen(a) + ft_strlen(hash_key)) : ft_strlen(a);
	pad(a, flag, hash_key, size, nb);
	if (flag->hash && !flag->minus && flag->width && nb != 0 && !flag->zero)
		ft_write(hash_key, ft_strlen(hash_key), flag);
	if (!flag->minus &&  ((nb != 0) || (nb == 0 && flag->precision != -1)))
		ft_write(a, ft_strlen(a), flag);
	free(a);
	return(ft_strlen(a));
}

void		ft_display_padding(t_flags *flag, uintmax_t nb, int *size, char *a)
{
	int			width;
	int			precision;

	width = 0;
	precision = flag->precision - *size;
	*size = (flag->precision > *size) ? flag->precision : *size;
	while (nb != 0 && flag->minus && width++ < precision && nb != 0)
		ft_write("0", 1, flag);
	if (flag->minus && flag->precision != -1)
		ft_write(a, ft_strlen(a), flag);
	width = 0;
	ft_width(*size + (nb == 0 ? 0 : 2), flag);
	width = 0;
	while (!flag->minus && width++ < precision)
		ft_write("0", 1, flag);
	*size += 2;
}


int			type_p(va_list args, t_flags *flag)
{
	int			size;
	uintmax_t	nb;
	int			tmp;
	char *a;

	flag->zero = (flag->precision) ? 0 : flag->zero;
	flag->length_type = LENGTH_L;
	nb = ft_get_nb_u(args, *flag);
	tmp = 0;
	if (nb == 0)
	{
		a = ft_strnew(5);
		a = "(nil)";
	}
	else
		a = ft_itoa_base(nb, 16);
	a = ft_strlow(a);
	size = ft_strlen(a);
	if ((!flag->width || flag->minus || flag->zero || flag->precision > size) && nb != 0)
	{
		tmp = 1;
		ft_write("0x", 2, flag);
	}
	ft_display_padding(flag, nb, &size, a);
	if (tmp == 0 && nb != 0)
		ft_write("0x", 2, flag);
	if (!flag->width || !flag->minus)
		ft_write(a, ft_strlen(a), flag);
	return (flag->width - size > 0 ? flag->width : size);
}
