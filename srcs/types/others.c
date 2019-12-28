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
	int size;

	(void)arg;
	size = ft_write("%", 1, flag);
	return (1);
}
