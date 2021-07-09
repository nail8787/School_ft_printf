#include "ft_printf.h"

static struct s_parser	prec0(struct s_parser pars)
{
	pars.flag = 0;
	while (pars.width > 0)
	{
		ft_putchar_fd(' ', 1);
		pars.width--;
		pars.count++;
	}
	pars.type = ' ';
	return (pars = clear_pars(pars));
}

static struct s_parser	str_flags(struct s_parser pars, char *str)
{
	if (pars.flag != 2)
	{
		while (pars.width > 0)
		{
			ft_putchar_fd(' ', 1);
			pars.width--;
			pars.count++;
		}
		ft_putstr_fd(str, 1);
	}
	if (pars.flag == 2)
	{
		ft_putstr_fd(str, 1);
		while (pars.width > 0)
		{
			ft_putchar_fd(' ', 1);
			pars.width--;
			pars.count++;
		}
	}
	return (pars);
}

struct s_parser			ft_s(va_list ap, struct s_parser pars)
{
	char	*str_unchanged;
	char	*str;

	str_unchanged = va_arg(ap, char *);
	if (pars.precision == 0)
		return (pars = prec0(pars));
	if (str_unchanged == NULL)
		str_unchanged = "(null)";
	str = ft_strdup(str_unchanged);
	if (!str)
		return (pars = error(pars));
	if ((pars.precision < (int)ft_strlen(str)) && pars.precision > 0)
		str[pars.precision] = '\0';
	pars.width = pars.width - ft_strlen(str);
	pars = str_flags(pars, str);
	pars.count = pars.count + ft_strlen(str);
	free_str(&str);
	return (pars = clear_pars(pars));
}
