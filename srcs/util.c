/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/25 15:15:00 by ssilvana          #+#    #+#             */
/*   Updated: 2019/12/25 15:15:03 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/struct.h"

intmax_t		ft_get_nb(va_list args, t_flags flags)
{
	intmax_t	nbr;

	nbr = va_arg(args, intmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (intmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (int)nbr;
	return (nbr);
}

uintmax_t		ft_get_nb_u(va_list args, t_flags flags)
{
	uintmax_t	nbr;

	nbr = va_arg(args, uintmax_t);
	if (flags.length_type == LENGTH_HH)
		nbr = (unsigned char)nbr;
	else if (flags.length_type == LENGTH_H)
		nbr = (unsigned short int)nbr;
	else if (flags.length_type == LENGTH_L)
		nbr = (unsigned long int)nbr;
	else if (flags.length_type == LENGTH_LL)
		nbr = (unsigned long long int)nbr;
	else if (flags.length_type == LENGTH_J)
		nbr = (uintmax_t)nbr;
	else if (flags.length_type == LENGTH_Z)
		nbr = (size_t)nbr;
	else
		nbr = (unsigned int)nbr;
	return (nbr);
}

void			edit_length(char **str, t_flags *flag, int c, int size)
{
	*str += size;
	if (flag->length_type < c)
		flag->length_type = c;
}

char			*ft_strcatbeg(char *s1, char *s2)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
	while (s1[i] != '\0')
	{
		tmp[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen(s1)] != '\0')
	{
		tmp[i] = s2[i - ft_strlen(s1)];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

char			*ft_strlow(char *a)
{
	int i;

	i = 0;
	while (a[i] != '\0')
	{
		if (a[i] <= 'Z' && a[i] >= 'A')
			a[i] = a[i] + 32;
		i++;
	}
	return (a);
}
