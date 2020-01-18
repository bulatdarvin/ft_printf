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
	while (width++ < flag->width - size)
		ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	return (width - 1);
}

int		ft_write(void *s, int size, t_flags *flag)
{
	int		i;
	char	*str;

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
	while (i < size)
		flag->buffer[flag->bytes++] = str[i++];
	flag->total_bytes += size;
	return (size);
}

int		write_until(char **str, t_flags *flag)
{
	int next;

	next = 0;
	while (**str != '%' && **str != '\0')
	{
		next++;
		next += color(str, flag);
		if (!(**str))
			break ;
		if (ft_strnequ(*str, "{eoc}", 5))
		{
			ft_write("\x1b[0m", 5, flag);
			*str = *str + 5;
			next = next + 5;
		}
		ft_write(*str, 1, flag);
		(*str)++;
	}
	return (next);
}
