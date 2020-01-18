/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstring.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 20:08:54 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/18 20:08:55 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

int		wchar_len(wint_t n)
{
	if (n < 0x007F)
		return (1);
	if (n < 0x07FF)
		return (2);
	if (n < 0xFFFF)
		return (3);
	if (n < 0x10FFFF)
		return (4);
	return (0);
}

int		wstring_len(wchar_t *s, int pre)
{
	int size;
	int tmp;

	size = 0;
	while (s && *s)
	{
		tmp = wchar_len(*s);
		if (tmp + size > pre && pre != 0)
			break ;
		size += tmp;
		s++;
	}
	return (size);
}

int		type_wstr(va_list arg, t_flags *flag)
{
	wchar_t		*s;
	int			size;
	int			i;

	s = va_arg(arg, wchar_t*);
	size = wstring_len(s, (flag->precision <= 0) ? 0 : flag->precision);
	if (!s)
		size = 6;
	size = flag->precision == -1 ? 0 : size;
	if (flag->precision > 0 && flag->precision < size && size > 0)
		size = flag->precision;
	if (flag->width && !flag->minus)
		ft_width(size, flag);
	if (!s)
		ft_write("(null)", (flag->precision > 0 && flag->precision < 6) ?
							flag->precision : 6, flag);
	i = 0;
	while (s && *s && i + wchar_len(*s) <= size)
		i += write_wchar(*s++, flag);
	if (flag->width && flag->minus)
		ft_width(size, flag);
	return (size + (flag->width - size > 0 ? flag->width - size : 0));
}
