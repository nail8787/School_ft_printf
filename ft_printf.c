#include "ft_printf.h"

static struct s_parser	check_format_width(va_list ap,
		const char *format, struct s_parser pars)
{
	if (*format >= '1' && *format <= '9')
	{
		pars.width = ft_atoi(format);
		format = pass(format, pars.width);
	}
	if (*format == '*')
	{
		pars.width = va_arg(ap, int);
		if (pars.width < 0)
		{
			pars.width *= -1;
			pars.flag = 2;
		}
		format++;
	}
	return (pars);
}

static struct s_parser	check_format_prec(va_list ap,
		const char *format, struct s_parser pars)
{
	pars.precision = 0;
	++format;
	if (*format == '*')
	{
		pars.precision = va_arg(ap, int);
		format++;
	}
	while (*format == '0')
		format++;
	if (*format > '0' && *format <= '9')
	{
		pars.precision = ft_atoi(format);
		format = pass(format, pars.precision);
	}
	if (pars.precision >= 0 && pars.flag == 1)
		pars.flag = 0;
	return (pars);
}

static struct s_parser	check_for_format(va_list ap,
		const char *format, struct s_parser pars)
{
	while (*format == '0' || *format == '-')
	{
		if (*format == '0' && pars.flag != 2)
			pars.flag = 1;
		if (*format == '-')
			pars.flag = 2;
		format++;
	}
	if ((*format >= '1' && *format <= '9') || *format == '*')
	{
		pars = check_format_width(ap, format, pars);
		while ((*format >= '0' && *format <= '9') || *format == '*')
			format++;
	}
	if (*format == '.')
	{
		pars = check_format_prec(ap, format, pars);
		format++;
		while ((*format >= '0' && *format <= '9') || *format == '*')
			format++;
	}
	pars.type = *format;
	return (pars);
}

struct s_parser			choose_type(va_list ap, struct s_parser pars)
{
	if (pars.type == 'd' || pars.type == 'i')
		pars = ft_di(ap, pars);
	if (pars.type == 'x' || pars.type == 'X')
		pars = ft_hex(ap, pars);
	if (pars.type == 'u')
		pars = ft_u(ap, pars);
	if (pars.type == 'c')
		pars = ft_c(ap, pars);
	if (pars.type == 's')
		pars = ft_s(ap, pars);
	if (pars.type == 'p')
		pars = ft_p(ap, pars);
	if (pars.type == '%')
		pars = ft_percent(pars);
	return (pars);
}

int						ft_printf(const char *format, ...)
{
	va_list			ap;
	struct s_parser pars;

	va_start(ap, format);
	pars = (struct s_parser){0, 0, -1, ' ', 0, 0, 0};
	while (*format != '\0')
	{
		while (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			format++;
			pars.count++;
			if (*format == '\0')
				return (pars.count);
		}
		format++;
		pars = check_for_format(ap, format, pars);
		format = ft_strchr(format, pars.type);
		format++;
		pars = choose_type(ap, pars);
		if (pars.error == -1)
			return (-1);
	}
	va_end(ap);
	return (pars.count);
}
