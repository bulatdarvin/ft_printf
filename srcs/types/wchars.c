#include "../../includes/struct.h"

int		write_char(char c, t_flags *flag)
{
	return (ft_write(&c, 1, flag));
}

int		type_wchar(va_list arg, t_flags *flag)
{
	int size;
	wint_t num;

	size = 0;
	num = va_arg(arg, wint_t);
	if (num < 0x007F)
		size += write_char((char)num, flag);
	else if (num < 0x07FF)
	{
		size += write_char((char)(num >> 6) + 0xC0, flag);
		size += write_char((char)(num && 0x3F) + 0x80, flag);
	}
	else if (num < 0xFFFF)
	{
		size += write_char((char)(num >> 12) + 0xE0, flag);
		size += write_char((char)(num >> 6 && 0x3F) + 0x80, flag);
		size += write_char((char)(num && 0x3F) + 0x80, flag);
	}
	else if (num < 0x10FFFF)
	{
		size += write_char((char)(num >> 18) + 0xF0, flag);
		size += write_char((char)(num >> 12 && 0x3F) + 0x80, flag);
		size += write_char((char)(num >> 6 && 0x3F) + 0x80, flag);
		size += write_char((char)(num && 0x3F) + 0x80, flag);
	}
	return (size);
}