#include "ft_printf.h"

struct s_parser	clear_pars(struct s_parser pars)
{
	pars.flag = 0;
	pars.width = 0;
	pars.precision = -1;
	pars.type = ' ';
	pars.sign = 0;
	return (pars);
}

struct s_parser	error(struct s_parser pars)
{
	pars.error = -1;
	return (pars);
}

const char		*pass(const char *format, int number)
{
	while (number > 0)
	{
		number = number / 10;
		format++;
	}
	return (format);
}

void			free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}
