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

int     calc_len(intmax_t c, int *size)
{
    int mod;

    mod = 1;
    while ((c / 10) != 0)
    {
        c = c / 10;
        (*size)++;
        mod = mod * 10; 
    }
    return (mod);
}

void    handle_main(long double *nb, char **str)
{
    char *s;

    s = *str;
    s = ft_strcat(s,ft_itoa((intmax_t)*nb));
    *nb = *nb - (intmax_t)*nb;
    *str = s;
}

void    handle_point(long double nb, char **str, int *i, int precision)
{
    uintmax_t tmp;
    char *s;

    s = *str;
	nb = nb * 10;
    s[(*i)++] = '.';
    while (precision-- > 0)
    {
        if ((uintmax_t)nb == 9)
            tmp = (uintmax_t)nb;
        else
            tmp = (uintmax_t)(nb + 0.01);
        s[(*i)++] = tmp + '0';
        nb = (nb - tmp) * 10;
    }
}

int     float_string(long double nb, char **s, int precision)
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
    calc_len((intmax_t)nb, &size);
    if (!(str = ft_strnew(size + precision + 1)))
        return (0);
    if (neg)
        str[i++] = '-';
    handle_main(&nb, &str);
	i = ft_strlen(str);
    handle_point(nb, &str, &i, precision);
    *s = str;
    return (size + precision + 1);    
}

int     type_f(va_list arg, t_flags *flag)
{
    int size;
	long double num;
    char *nb;

    if (flag->precision <= 0)
        flag->precision = 6;
    if (flag->length_type == LENGTH_LL)
        num = va_arg(arg, long double);
    else
        num = va_arg(arg, double);
    size = float_string((flag->length_type == LENGTH_LL ? (long double)num : (double)num), &nb, flag->precision);
    ft_write(nb, size, flag);
    free(nb);
    return (size);
}