/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   longs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/18 19:37:42 by ssilvana          #+#    #+#             */
/*   Updated: 2020/01/18 19:37:44 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

int		type_u_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_u(args, flags));
}

int		type_d_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_d(args, flags));
}

int		type_o_upper(va_list args, t_flags *flags)
{
	flags->length_type = LENGTH_L;
	return (type_o(args, flags));
}
