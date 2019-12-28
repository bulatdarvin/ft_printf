#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
#include <unistd.h>
#include "includes/struct.h"

t_types	g_types[ARG_CNT] = {
	{'c', type_c}, {'d', type_d}, {'i', type_d}, {'s', type_s}, {'u', type_u}, 
	{'o', type_o}, {'x', type_x}, {'X', type_x_upper}, {'f', type_f}, {'%', type_percent}/*{'C', type_c_upper}, {'S', type_s_upper},
	{'p', type_p},
	{'D', type_d_upper}, {'O', type_o_upper}, {'U', type_u_upper},
	{'a', type_a}, {'A', type_a_upper}, {'b', type_b}, {'n', type_n}*/ 
};


intmax_t	ft_get_nb(va_list args, t_flags flags)
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

int		type_percent(va_list arg, t_flags *flag)
{
	int size;

	size = ft_write("%", 1, flag);
	return (1);
}

int		type_u(va_list arg, t_flags *flag)
{
	uintmax_t nb;
	int precision;
	char *a;
	char *tmp;
	int i;

	nb = ft_get_nb(arg, *flag);
	a = ft_itoa_base(nb, 10);
	precision = flag->precision - ft_strlen(a);
	i = 0;
	tmp = ft_strnew(precision);
	while (i < precision)
	{
		tmp[i] = '0';
		i++;
	}
	ft_strcat(tmp, a);
	flag->zero = 0;
	i = ft_write(tmp, ft_strlen(tmp), flag);
	return (i);
}

int		type_x(va_list arg, t_flags *flag)
{
	intmax_t nb;
	size_t i;
	char *a;
	int size;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 16);
	i = 0;
	while (i < ft_strlen(a))
	{
		a[i] = ft_tolower(a[i]);
		i++;
	}
	if (flag->hash && nb != 0)
	{
		flag->buffer[flag->bytes++] = '0';
		flag->buffer[flag->bytes++] = 'x';
		flag->total_bytes += 2; 
	}
	size = ft_write(a, ft_strlen(a), flag);
	return (size);	
}

int		type_x_upper(va_list arg, t_flags *flag)
{
	intmax_t nb;
	char *a;
	int size;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 16);
	if (flag->hash && nb != 0)
	{
		flag->buffer[flag->bytes++] = '0';
		flag->buffer[flag->bytes++] = 'x';
		flag->total_bytes += 2; 
	}
	size = ft_write(a, ft_strlen(a), flag);
	return (size);

}

int		type_o(va_list arg, t_flags *flag)
{
	intmax_t nb;
	int size;
	char *a;

	nb = ft_get_nb(arg, *flag);
	if (nb < 0)
		nb = MAX - FT_ABS(nb) + 1;
	a = ft_itoa_base(nb, 8);
	if (flag->hash && nb != 0)
	{
		flag->buffer[flag->bytes++] = '0';
		flag->total_bytes += 1; 
	}
	size = ft_write(a, ft_strlen(a), flag);
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

int     type_d(va_list arg, t_flags *flag)
{
    int size;
    long long c;
	char *a;
	char *tmp;
	int precision;

    c = ft_get_nb(arg, *flag);
	a = ft_itoa(c);
	precision = flag->precision - ft_strlen(a) + (flag->plus ? 1 : 0);
	if (!(tmp = ft_strnew(precision)) && precision > 0)
		return (0);
	size = 0;
	if (flag->plus)
	{
		size++;
		flag->buffer[flag->bytes++] = '+';
		flag->total_bytes++;
		flag->width--;
	}
	while (size++ < precision - 1 && precision > 0)
		tmp[size - 1] = '0';
	if (tmp)
		ft_strcat(tmp, a);
	else
		tmp = a;
    size = ft_write(tmp, ft_strlen(tmp), flag);
    return (size);
}

int     type_c(va_list arg, t_flags *flag)
{
    int c;
	int size;

    c = va_arg(arg, int);
	size = ft_write(&c, 1, flag);
    return (size);
}

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
    int mod;
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
    mod = calc_len(nb, &size);
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

int	ft_width(char *str, t_flags *flag, int *i)
{
	int width;
	size_t k;

	width = 0;
	k = 0;
	if (flag->width && flag->width > (int)ft_strlen(str))
	{
		if (flag->minus)
			while (k++ < ft_strlen(str))
				flag->buffer[flag->bytes++] = str[(*i)++]; 
		while (width++ < flag->width - (int)ft_strlen(str) /*+ flag->precision*/)
			flag->buffer[flag->bytes++] = (flag->zero && !flag->minus) ? '0' : ' ';
		if (!flag->minus)
			while (k++ < ft_strlen(str))
				flag->buffer[flag->bytes++] = str[(*i)++]; 
		flag->width = 0;
		width--;
	}
	return (width);
}

int		ft_write(void *s, int size, t_flags *flag)
{
	int		i;
	char	*str;
	int		width;
	int tmp;

	width = 0;
	i = 0;

	str = (char*)s;
	if (flag->bytes + size > BUFF_SIZE)
	{
		write(1, flag->buffer, (size_t)flag->bytes);
		flag->bytes = 0;
		if (size > BUFF_SIZE)
		{
			write(1, s, (size_t)size);
			return (size);
		}
	}
	tmp = ft_width(str, flag, &i);
	//ft_putnbr(size);
	//ft_putchar('\n');
	while (i < size)
		flag->buffer[flag->bytes++] = str[i++];
	size += tmp;
	flag->total_bytes += size;
	return (size);
}

int		write_until(char **str, t_flags *flag)
{
	int next;

	if (ft_strchr(*str, '%'))
		next = (int)(ft_strchr(*str, '%') - *str);
	else
		next = (int)ft_strlen(*str);
	ft_write(*str, next, flag);
	*str += next;
	return (next);
}

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
		flag->hash = 1;
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

void	edit_length(char **str, t_flags *flag, int c, int size)
{
	*str += size;

	if (flag->length_type < c)
		flag->length_type = c;
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

int		call_type(char **str, va_list args, t_flags *flag)
{
	int arg;
	int size;

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
	size = 1;
//	ft_putchar(**str);
	if (arg == ARG_CNT)
	{
		flag->buffer[flag->bytes++] = **str;
		return (2);
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
	int		tmp;
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
			tmp = handle(&str, argc, &flags);
			bytes += tmp;
			if (tmp == 0)
			{
				ft_putstr("error");
				return (0);
			}
		}
		else
			bytes += write_until(&str, &flags);
	va_end(argc);
//	ft_putchar(flags.buffer[1]);
//	ft_putchar('\n');
	if (flags.bytes > 0)
		write(1, flags.buffer, flags.bytes);
	return (flags.total_bytes);
}

char	*ft_strcatbeg(char *s1, char *s2)
{
	char *tmp;
	int i;

	i = 0;
	tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
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


int main()
{
	int c = 10000;
	char *a;
	int b = 20;
	//ft_putstr(ft_strcatbeg(a, "123"));
	//int size = 1;
	//char *s;
	//size = float_string(a, &s, 15);
printf("%#08u", 42);
//ft_putnbr(ft_printf("test"));
//	printf("% ++d", b);
	//printf("%p\n", a);
	//printf("%05d\n", 100);
}
