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

void	hash_and_sign(char *str, t_flags *flag, int *i)
{
	if (str[*i] == '-' || str[*i] == '+')
		flag->buffer[flag->bytes++] = str[(*i)++];
	if (flag->hash)
	{
		if (flag->type == 'x' && str[*i] != '0' && str[(*i) + 1] != '0')
		{
			flag->buffer[flag->bytes++] = '0';
			flag->buffer[flag->bytes++] = 'x';
			flag->total_bytes += 2; 
		}
		if (flag->type == 'X' && str[*i] != '0' && str[(*i) + 1] != '0')
		{
			flag->buffer[flag->bytes++] = '0';
			flag->buffer[flag->bytes++] = 'X';
			flag->total_bytes += 2; 
		}
		if (flag->type == 'o' && str[*i] != '0' && str[(*i) + 1] != '0')
		{
			flag->buffer[flag->bytes++] = '0';
			flag->total_bytes += 1;
		}	
	}
}


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
/*int		ft_width(char *str, t_flags *flag, int *i)
{
	int width;
	size_t k;

	width = 0;
	k = 0;
	if (flag->width && flag->width > (int)ft_strlen(str))
	{
		if (flag->minus)
		{
			//hash_and_sign(str, flag, i);
			while (k++ < ft_strlen(str))
				flag->buffer[flag->bytes++] = str[(*i)++];
		}
		while (width++ < flag->width - (int)ft_strlen(str) - flag->hash)
			flag->buffer[flag->bytes++] = (flag->zero && !flag->minus) ? '0' : ' ';
		if (!flag->minus)
		{
			//hash_and_sign(str, flag, i);
			while (k++ < ft_strlen(str))
				flag->buffer[flag->bytes++] = str[(*i)++];
		}
		flag->width = 0;
		width--;
	}
	return (width);
}*/



int		ft_width(char *str, t_flags *flag)
{
	int width;

	width = 0;
	if (flag->width > flag->precision)
		while (width++ < flag->width - (int)ft_strlen(str))
			ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	return (width);
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
