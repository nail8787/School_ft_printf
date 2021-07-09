#include "ft_printf.h"

struct s_parser	ft_c(va_list ap, struct s_parser pars)
{
	unsigned char c;

	c = (unsigned char)va_arg(ap, int);
	pars.width--;
	if (pars.flag == 2)
	{
		ft_putchar_fd(c, 1);
		pars.count++;
		while (pars.width-- > 0)
		{
			ft_putchar_fd(' ', 1);
			pars.count++;
		}
	}
	if (pars.flag == 0)
	{
		while (pars.width-- > 0)
		{
			ft_putchar_fd(' ', 1);
			pars.count++;
		}
		ft_putchar_fd(c, 1);
		pars.count++;
	}
	return (pars = clear_pars(pars));
}
