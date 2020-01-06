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
/*
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
*/
int		write_d(char *a, int size, int precision, t_flags *flag, intmax_t nb)
{
	int width;
	int pre_width;

	pre_width = 0;
	if (!flag->minus)
	{
		if (flag->width && flag->zero)
			sign(nb, flag);
		width = ft_width(a, flag);
	}
	if ((flag->width && (flag->minus || !flag->zero)) || !flag->width)
		sign(nb, flag);
	while (pre_width++ < precision)
		ft_write("0", 1, flag);
	if (flag->precision != -1)
		ft_write(a, ft_strlen(a), flag);
	return (width + ft_strlen(a));
}

int     type_d(va_list arg, t_flags *flag)
{
    int size;
    intmax_t nb;
	char *a;
	int precision;

    nb = ft_get_nb(arg, *flag);
	a = ft_itoa(FT_ABS(nb));
	precision = flag->precision - ft_strlen(a);
	size = (flag->precision > ft_strlen(a)) ? flag->precision : ft_strlen(a);
	size += ((nb >= 0 && (flag->plus || flag->space)) || nb < 0) ? 1 : 0;
    size = write_d(a, size, precision, flag, nb);
	size = (flag->minus) ? ft_width(a, flag) : size;
    return (size - 1);
}

char	*ft_strlow(char *a)
{
	int i;

	i = 0;
	while (i < ft_strlen(a))
		a[i] = ft_tolower(a[i++]);
	return (a);
}

void	pad(char *a, t_flags *flag, char *hash_key)
{
	int width;
	int precision;

	if (flag->precision <= 0 && flag->width <= 0)
		return ;
	precision = flag->precision - ft_strlen(a);
	precision = (flag->precision > ft_strlen(a)) ? precision : 0;
	width = 0;
	while (flag->minus && width++ < precision)
		ft_write("0", 1, flag);
	if (flag->minus && flag->precision != -1)
		ft_write(a, ft_strlen(a), flag);
	width = 0;
	//if (flag->minus)
	//	a = ft_strcatbeg(hash_key, a);
//	if (flag->precision != -1 && a == "0")
//	{
//		free(a);
//		a = ft_strnew(0);
		ft_width(a, flag);
//	}
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
	if (flag->hash && flag->minus && nb != 0)
		ft_write(hash_key, ft_strlen(hash_key), flag);
	pad(a, flag, hash_key);
	if (flag->hash && flag->width && !flag->minus && !flag->zero && flag->precision != -1)
		ft_write(hash_key, ft_strlen(hash_key), flag);
	if (!flag->minus && flag->precision != -1)
		ft_write(a, ft_strlen(a), flag);
	return(ft_strlen(a));
}

