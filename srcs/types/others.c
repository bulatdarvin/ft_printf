/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/27 18:51:15 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/27 18:51:18 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/struct.h"

int		type_percent(va_list arg, t_flags *flag)
{
	int		width;

	(void)arg;
	if (flag->width)
	{
		if (flag->minus)
			ft_write("%", 1, flag);
		width = 0;
		while (width++ < flag->width - 1)
			ft_write((flag->zero && !flag->minus) ? "0" : " ", 1, flag);
	}
	if (!flag->width || !flag->minus)
		ft_write("%", 1, flag);
	return ((flag->width) ? flag->width : 1);
}
