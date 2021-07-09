#include "ft_printf.h"

struct s_parser		num0_prec0(struct s_parser pars)
{
	pars.precision = -1;
	pars.flag = 0;
	while (pars.width > 0)
	{
		ft_putchar_fd(' ', 1);
		pars.width--;
		pars.count++;
	}
	pars.type = ' ';
	return (pars);
}

static unsigned int	size_of_uint(unsigned int buf)
{
	unsigned int count;

	count = 0;
	if (buf == 0)
		return (1);
	while (buf != 0)
	{
		buf = buf / 10;
		count++;
	}
	return (count);
}

static char			*ft_itoa_unsigned(unsigned int num,
		unsigned int len, char *str)
{
	str[len--] = '\0';
	if (num == 0)
		str[len] = '0';
	while (num != 0)
	{
		str[len--] = num % 10 + '0';
		num /= 10;
	}
	return (str);
}

struct s_parser		ft_u(va_list ap, struct s_parser pars)
{
	unsigned int	num;
	char			*num_str;
	unsigned int	len;

	num = va_arg(ap, unsigned int);
	if (num == 0 && pars.precision == 0)
		return (num0_prec0(pars));
	len = size_of_uint(num);
	num_str = (char *)malloc((len + 1) * sizeof(char));
	if (!num_str)
		return (pars = error(pars));
	num_str = ft_itoa_unsigned(num, len, num_str);
	pars = compare_prec_and_width(pars, num_str);
	if (pars.flag < 2)
		pars = ft_di_flags_0_or_1(pars, num_str);
	if (pars.flag == 2)
		pars = ft_di_flag_2(pars, num_str);
	free_str(&num_str);
	return (pars = clear_pars(pars));
}
