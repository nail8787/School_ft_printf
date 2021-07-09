#include "ft_printf.h"

static struct s_parser	perc_flag_0(struct s_parser pars)
{
	while (pars.width > 0)
	{
		ft_putchar_fd(' ', 1);
		pars.width--;
		pars.count++;
	}
	ft_putchar_fd('%', 1);
	pars.count++;
	return (pars);
}

static struct s_parser	perc_flag_2(struct s_parser pars)
{
	ft_putchar_fd('%', 1);
	pars.count++;
	while (pars.width > 0)
	{
		ft_putchar_fd(' ', 1);
		pars.width--;
		pars.count++;
	}
	return (pars);
}

struct s_parser			ft_percent(struct s_parser pars)
{
	pars.width--;
	if (pars.flag == 1)
	{
		while (pars.width > 0)
		{
			ft_putchar_fd('0', 1);
			pars.width--;
			pars.count++;
		}
		ft_putchar_fd('%', 1);
		pars.count++;
	}
	if (pars.flag == 0)
		pars = perc_flag_0(pars);
	if (pars.flag == 2)
		pars = perc_flag_2(pars);
	return (pars = clear_pars(pars));
}
