#include "ft_printf.h"

struct s_parser	compare_prec_and_width(struct s_parser pars,
		char *num_str)
{
	if (pars.precision <= (int)ft_strlen(num_str))
		pars.precision = 0;
	if (pars.precision > (int)ft_strlen(num_str))
		pars.precision = pars.precision - ft_strlen(num_str);
	if (pars.width <= pars.precision + (int)ft_strlen(num_str))
		pars.width = 0;
	if (pars.width > pars.precision + (int)ft_strlen(num_str))
	{
		pars.width = pars.width - (pars.precision + (int)ft_strlen(num_str));
		if (pars.sign == -1)
			pars.width--;
	}
	pars.count = pars.count + pars.width + pars.precision + ft_strlen(num_str);
	if (pars.sign == -1)
		pars.count++;
	return (pars);
}

struct s_parser	ft_di_flag_2(struct s_parser pars,
		char *num_str)
{
	if (pars.sign == -1)
		ft_putchar_fd('-', 1);
	while (pars.precision != 0)
	{
		ft_putchar_fd('0', 1);
		pars.precision--;
	}
	ft_putstr_fd(num_str, 1);
	while (pars.width != 0)
	{
		ft_putchar_fd(' ', 1);
		pars.width--;
	}
	return (pars);
}

struct s_parser	ft_di_flags_0_or_1(struct s_parser pars,
		char *num_str)
{
	if (pars.sign == -1 && pars.flag == 1 && pars.precision == 0)
		ft_putchar_fd('-', 1);
	while (pars.width != 0)
	{
		if (pars.flag == 1 && pars.precision == 0)
			ft_putchar_fd('0', 1);
		else
			ft_putchar_fd(' ', 1);
		pars.width--;
	}
	if ((pars.sign == -1 && pars.flag == 0) ||
			(pars.sign == -1 && pars.flag == 1 && pars.precision > 0))
		ft_putchar_fd('-', 1);
	while (pars.precision != 0)
	{
		ft_putchar_fd('0', 1);
		pars.precision--;
	}
	ft_putstr_fd(num_str, 1);
	return (pars);
}

struct s_parser	ft_di(va_list ap, struct s_parser pars)
{
	char	*num_str;
	int		num;

	num = va_arg(ap, int);
	if (num == 0 && pars.precision == 0)
		return (num0_prec0(pars));
	if (num < 0)
	{
		pars.sign = -1;
		if (num != INT_MIN)
			num = num * -1;
	}
	if (num == INT_MIN)
		num_str = ft_strdup("2147483648");
	else
		num_str = ft_itoa(num);
	if (!num_str)
		return (pars = error(pars));
	pars = compare_prec_and_width(pars, num_str);
	if (pars.flag < 2)
		pars = ft_di_flags_0_or_1(pars, num_str);
	if (pars.flag == 2)
		pars = ft_di_flag_2(pars, num_str);
	free_str(&num_str);
	return (pars = clear_pars(pars));
}
