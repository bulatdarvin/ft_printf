/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssilvana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:13:11 by ssilvana          #+#    #+#             */
/*   Updated: 2019/10/13 18:13:12 by ssilvana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# define BUFF_SIZE 1024
# define ARG_CNT 17
# define FT_ABS(x) ((x < 0) ? (-x):(x))
# define LENGTH_HH 1
# define LENGTH_H 2
# define LENGTH_LL 4
# define LENGTH_L 3
# define LENGTH_J 6
# define LENGTH_Z 5
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdarg.h>
# include <math.h>
# include <unistd.h>
# include <inttypes.h>
# include <wchar.h>

typedef struct	s_flags
{
	int			hash;
	int			zero;
	int			plus;
	int			minus;
	int			space;
	int			width;
	int			precision;
	char		type;
	char		buffer[BUFF_SIZE];
	int			bytes;
	int			total_bytes;
	int			length_type;
}				t_flags;

typedef struct	s_types
{
	char		name;
	int			(*f)();
}				t_types;

int				ft_printf(const char *format, ...);
int				handle(char **str, va_list arg, t_flags *flag);
int				call_type(char **str, va_list args, t_flags *flag);
int				ft_pad(t_flags *flag, int size);
int				handle_length(char **str, t_flags *flag);
void			edit_length(char **str, t_flags *flag, int c, int size);
int				handle_precision(char **str, t_flags *flag, va_list args);
int				handle_width(char **str, t_flags *flag, va_list args);
int				handle_flags(char **str, t_flags *flag);
void			init_flags(t_flags *flag);
int				write_until(char **str, t_flags *flag);
int				ft_write(void *s, int size, t_flags *flag);
int				ft_width(int size, t_flags *flag);
intmax_t		ft_get_nb(va_list args, t_flags flags);
uintmax_t		ft_get_nb_u(va_list args, t_flags flags);
int				sign(intmax_t nb, t_flags *flag);
int				type_char(va_list arg, t_flags *flag);
int				type_f(va_list arg, t_flags *flag);
int				type_d(va_list arg, t_flags *flag);
int				type_s(va_list arg, t_flags *flag);
int				type_u(va_list arg, t_flags *flag);
int				type_o(va_list arg, t_flags *flag);
int				type_x(va_list arg, t_flags *flag);
int				type_p(va_list arg, t_flags *flag);
int				type_percent(va_list arg, t_flags *flag);
int				type_x_upper(va_list arg, t_flags *flag);
int				type_wchar(va_list arg, t_flags *flag);
int				type_u_upper(va_list args, t_flags *flags);
int				type_d_upper(va_list args, t_flags *flags);
int				type_wstr(va_list arg, t_flags *flag);
int				type_o_upper(va_list args, t_flags *flags);
int				type_b(va_list arg, t_flags *flag);
int				write_d(char *a, int size, t_flags *flag, intmax_t nb);
int				calc_len(intmax_t c, int *size);
void			handle_main(long double *nb, char **str);
void			handle_point(long double nb, char **str, int *i, int precision);
int				float_string(long double nb, char **s, int precision);
char			*ft_strcatbeg(char *s1, char *s2);
int				write_char(char c, t_flags *flag);
int				color(char **str, t_flags *flag);
int				help_to_base(va_list a, t_flags *f, uintmax_t b, char *h);
char			*ft_strlow(char *a);
int				write_wchar(wint_t num, t_flags *flag);
void			p_padding(t_flags *flag, uintmax_t nb, int *size, char *a);
void			pad(char *a, t_flags *flag, char *hash_key, int nb);
int				write_d(char *a, int size, t_flags *flag, intmax_t nb);

#endif
