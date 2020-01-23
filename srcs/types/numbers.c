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

int		type_d(va_list arg, t_flags *flag)
{
	int			size;
	intmax_t	nb;
	char		*a;

	nb = ft_get_nb(arg, *flag);
	a = ft_itoa(ft_abs(nb));
	if (flag->precision != 0)
		flag->zero = 0;
	size = (flag->precision > (int)ft_strlen(a)) ?
		flag->precision : ft_strlen(a);
	size = (flag->precision == -1 && nb == 0) ? 0 : size;
	size += ((nb >= 0 && (flag->plus || flag->space)) || nb < 0) ? 1 : 0;
	size = write_d(a, size, flag, nb);
	size = (flag->minus) ? ft_width(size, flag) : size;
	free(a);
	return (size);
}
