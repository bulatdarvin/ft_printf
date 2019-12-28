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

int     type_c(va_list arg, t_flags *flag)
{
    int c;
	int size;

    c = va_arg(arg, int);
	size = ft_write(&c, 1, flag);
    return (size);
}


int 	type_s(va_list arg, t_flags *flag)
{
	char *a;
	int size;

	a = va_arg(arg, char*);
	if (a == NULL)
	{
		a = ft_strnew(6);
		a = "(null)";
	}
	if (flag->precision > 0 && flag->precision < (int)ft_strlen(a))
		size = flag->precision;
	else
		size = ft_strlen(a);
	size = ft_write(a, size, flag);
	return (size);	
}
