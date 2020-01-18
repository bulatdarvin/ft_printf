/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chars.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:07:11 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:07:13 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

int		type_char(va_list arg, t_flags *flag)
{
	int c;
	int width;

	c = va_arg(arg, int);
	width = 0;
	if (flag->width)
	{
		if (flag->minus)
			ft_write(&c, 1, flag);
		while (width++ < flag->width - 1)
			ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	}
	if (!flag->minus)
		ft_write(&c, 1, flag);
	return (flag->width ? width : 1);
}

int		type_s(va_list arg, t_flags *flag)
{
	char	*s;
	int		size;

	s = va_arg(arg, char*);
	if (!s)
		size = 6;
	else
		size = (int)ft_strlen(s);
	size = (flag->precision == -1) ? 0 : size;
	if (flag->precision > 0 && flag->precision < size && size > 0)
		size = flag->precision;
	if (flag->width && s)
	{
		if (flag->minus)
			ft_write(s, size, flag);
		ft_width(size, flag);
	}
	if (flag->width <= 0 || !flag->minus || !s)
		ft_write((s) ? s : "(null)", size, flag);
	if (!s)
		ft_width(size, flag);
	return (size + (flag->width - size > 0 ? flag->width - size : 0));
}
