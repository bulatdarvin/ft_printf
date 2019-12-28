/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:11:07 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:11:09 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

void	init_flags(t_flags *flag)
{
	flag->hash = 0;
	flag->zero = 0;
	flag->minus = 0;
	flag->plus = 0;
	flag->space = 0;
	flag->width = 0;
	flag->precision = 0;
	flag->length_type = 0;
	flag->type = '\0';
}

int		handle_flags(char **str, t_flags *flag)
{
	if (**str == '0')
		flag->zero = 1;
	else if (**str == '-')
		flag->minus = 1;
	else if (**str == '+')
		flag->plus = 1;
	else if (**str == '#')
		flag->hash = 2;
	else if (**str == ' ')
		flag->space = 1;
	else
		return (0);
	(*str)++;
	return (1);
}

int		handle_width(char **str, t_flags *flag, va_list args)
{
	int width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
				flag->minus = 1;
			flag->width = (width < 0 ? (-width):(width));
			width = 1;
		}
		else
			flag->width = width;
		while (width > 0 && (*str += 1))
			width /= 10;
		return (1);
	}
	return (0);
}

int		handle_precision(char **str, t_flags *flag, va_list args)
{
	int presicion;

	if (**str == '.')
	{
		(*str)++;
		if (ft_isdigit(**str) == 0 && **str != '*')
		{
			flag->precision = -1;
			return (1);
		}
		presicion = (**str == '*' ? va_arg(args, int) : ft_atoi(*str));
		flag->precision = (presicion == 0 ? -1 : presicion);
		if (flag->precision < 0 && flag->precision != -1)
			flag->precision = 0;
		if (**str == '*')
			presicion = 1;
		else if (presicion == 0)
			(*str)++;		
		while (presicion > 0 && (*str += 1))
			presicion /= 10;
		return (1);
	}
	return (0);
}

int 	handle_length(char **str, t_flags *flag)
{
	if (**str == 'h' && *(*str + 1) == 'h')
		edit_length(str, flag, LENGTH_HH, 2);
	else if (**str == 'h')
		edit_length(str, flag, LENGTH_H, 1);
	else if (**str == 'l' && *(*str + 1) == 'l')
		edit_length(str, flag, LENGTH_LL, 2);
	else if (**str == 'l')
		edit_length(str, flag, LENGTH_L, 1);
	else if (**str =='j')
		edit_length(str, flag, LENGTH_J, 1);
	else if (**str == 'z')
		edit_length(str, flag, LENGTH_Z, 1);
	else
		return (0);
	return (1);
}