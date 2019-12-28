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
	uintmax_t nb;
	int precision;
	char *a;
	char *tmp;
	int i;

	nb = ft_get_nb_u(arg, *flag);
	a = ft_itoa_base(nb, 10);
	precision = flag->precision - ft_strlen(a);
	i = 0;
	if (precision > 0)
		tmp = ft_strnew(precision);
	while (i < precision && precision > 0)
		tmp[i++] = '0';
	tmp = (precision > 0) ? ft_strcatbeg(tmp, a) : a;
	flag->zero = 0;
	if (flag->precision == -1)
		a = ft_strnew(0);
	i = ft_write(tmp, ft_strlen(tmp), flag);
	return (i);
}

int		type_x(va_list arg, t_flags *flag)
{
	intmax_t nb;
	size_t i;
	char *a;
	int size;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 16);
	i = 0;
	while (i < ft_strlen(a))
	{
		a[i] = ft_tolower(a[i]);
		i++;
	}
	if (flag->hash && nb != 0)
	{
		flag->buffer[flag->bytes++] = '0';
		flag->buffer[flag->bytes++] = 'x';
		flag->total_bytes += 2; 
	}
	if (flag->precision == -1)
		a = ft_strnew(0);
	size = ft_write(a, ft_strlen(a), flag);
	return (size);	
}

int		type_x_upper(va_list arg, t_flags *flag)
{
	intmax_t nb;
	char *a;
	int size;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 16);
	if (flag->hash && nb != 0 && flag->precision > 0)
	{
		flag->buffer[flag->bytes++] = '0';
		flag->buffer[flag->bytes++] = 'X';
		flag->total_bytes += 2; 
	}
	if (flag->precision == -1)
		a = ft_strnew(0);
	size = ft_write(a, ft_strlen(a), flag);
	return (size);

}

int		type_o(va_list arg, t_flags *flag)
{
	intmax_t nb;
	int size;
	char *a;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 8);
	if (flag->hash && nb != 0)
		a = ft_strcatbeg("0", a);
	if (flag->precision == -1)
		a = ft_strnew(0);
	size = ft_write(a, ft_strlen(a), flag);
	return (size);		
}


int     type_d(va_list arg, t_flags *flag)
{
    int size;
    long long c;
	char *a;
	char *tmp;
	int precision;

    c = ft_get_nb(arg, *flag);
	a = ft_itoa(c);
	precision = flag->precision - ft_strlen(a) + (flag->plus ? 1 : 0);
	if (!(tmp = ft_strnew(precision)) && precision > 0)
		return (0);
	size = 0;
	if (flag->plus && c >= 0)
	{
		a = ft_strcatbeg("+", a);
	/*	size++;
		flag->buffer[flag->bytes++] = '+';
		flag->total_bytes++;
		flag->width--;
	*/}
	while (size++ < precision && precision > 0)
		tmp[size - 1] = '0';
	if (tmp)
		ft_strcat(tmp, a);
	else
		tmp = a;
    size = ft_write(tmp, ft_strlen(tmp), flag);
    return (size);
}

