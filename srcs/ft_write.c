/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:13:14 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:13:17 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

int		sign(intmax_t nb, t_flags *flag)
{
	if (nb < 0)
		ft_write("-", 1, flag);
	if (flag->plus && nb >= 0)
		ft_write("+", 1, flag);
	else if (flag->space && nb >= 0)
		ft_write(" ", 1, flag);
	return (1);
}

int		ft_width(int size, t_flags *flag)
{
	int width;

	width = 0;
	//if (flag->width > flag->precision)
		while (width++ < flag->width - size)
			ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	return (width - 1);
}

int		ft_write(void *s, int size, t_flags *flag)
{
	int		i;
	//int		tmp;
	char	*str;
	//int		width;

	//width = 0;
	i = 0;

	str = (char*)s;
	if (flag->bytes + size > BUFF_SIZE)
	{
		write(1, flag->buffer, (size_t)flag->bytes);
		flag->bytes = 0;
		if (size > BUFF_SIZE)
		{
			write(1, s, (size_t)size);
			return (size);
		}
	}
	//tmp = ft_width(str, flag, &i);
	while (i < size)
		flag->buffer[flag->bytes++] = str[i++];
	flag->total_bytes += size;
	return (size);
}

int		write_until(char **str, t_flags *flag)
{
	int next;

	if (ft_strchr(*str, '%'))
		next = (int)(ft_strchr(*str, '%') - *str);
	else
		next = (int)ft_strlen(*str);
	ft_write(*str, next, flag);
	*str += next;
	return (next);
}
