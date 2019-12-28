/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:14:21 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:14:23 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

t_types	g_types[ARG_CNT] = {
	{'c', type_c}, {'d', type_d}, {'i', type_d}, {'s', type_s}, {'u', type_u}, 
	{'o', type_o}, {'x', type_x}, {'X', type_x_upper}, {'f', type_f}, {'%', type_percent}/*{'C', type_c_upper}, {'S', type_s_upper},
	{'p', type_p},
	{'D', type_d_upper}, {'O', type_o_upper}, {'U', type_u_upper},
	{'a', type_a}, {'A', type_a_upper}, {'b', type_b}, {'n', type_n}*/ 
};

int		call_type(char **str, va_list args, t_flags *flag)
{
	int arg;
	
	arg = 0;
	while (arg < ARG_CNT)
	{
		if (**str == g_types[arg].name)
		{
			(*str)++;
			flag->type = g_types[arg].name;
			return (g_types[arg].f(args, flag));
		}
		arg++;
	}
	if (arg == ARG_CNT)
	{
		flag->buffer[flag->bytes++] = **str;
		flag->total_bytes++;
	}
	*str += 1;
	return (1);
}

int		handle(char **str, va_list arg, t_flags *flag)
{
	int	found;

	init_flags(flag);
    found = 0;
	while(**str)
	{
		found = 0;
		while (handle_length(str, flag) || handle_flags(str, flag) || handle_width(str, flag, arg) || handle_precision(str, flag, arg))
			found = 1;
		if (ft_isalpha(**str) || **str == '%')
			return (call_type(str, arg, flag));
		if (*(*str + 1) == '\0' || found == 0)
			return (0);
	}
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list argc;
	t_flags flags;
	char	*str;
	int		bytes;

	bytes = 0;
	flags.bytes = 0;
	flags.total_bytes = 0;
	va_start(argc, format);
	str = (char*)format;
	while (*str)
		if (*str == '%')
		{
			str++;
			bytes += handle(&str, argc, &flags);
		}
		else
			bytes += write_until(&str, &flags);
	va_end(argc);
	if (flags.bytes > 0)
		write(1, flags.buffer, flags.bytes);
	return (flags.total_bytes);
}
