/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:06:57 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:06:59 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

int     calc_len(double c, int *size)
{
    int mod;

    mod = 1;
    while ((int)(c / 10) != 0)
    {
        c = c / 10;
        (*size)++;
        mod = mod * 10; 
    }
    return (mod);
}

void    handle_main(double *nb, char **str)
{
    char *s;

    s = *str;
    s = ft_strcat(s,ft_itoa((int)*nb));
    *nb = *nb - (int)*nb;
    *str = s;
}

void    handle_point(double nb, char **str, int *i, int precision)
{
    int tmp;
    char *s;

    s = *str;
	nb = nb * 10;
    s[(*i)++] = '.';
    while (precision-- > 0)
    {
        if ((int)nb == 9)
            tmp = (int)nb;
        else
            tmp = (int)(nb + 0.01);
        s[(*i)++] = tmp + '0';
        nb = (nb - tmp)*10;
    }
}

int     float_string(double nb, char **s, int precision)
{
    int neg;
    int size;
    char *str;
    int i;

    neg = 0;
    i = 0;
    size = 1;
    if (nb < 0 && size++)
    {
        nb = -nb;
        neg = 1;
    }
    if (!(str = ft_strnew(size + precision + 1)))
        return (0);
    if (neg)
        str[i++] = '-';
    handle_main(&nb, &str);	
	i = i + ft_strlen(str) - 1;
    handle_point(nb, &str, &i, precision);
    *s = str;
    return (size + precision + 1);    
}

int     type_f(va_list arg, t_flags *flag)
{
    int size;
	double num;
    char *nb;

    if (flag->precision <= 0)
        flag->precision = 7;
	num = va_arg(arg, double);
    size = float_string((flag->length_type == LENGTH_L ? (long double)num : num), &nb, flag->precision);
    ft_write(nb, size, flag);
    return (size);
}