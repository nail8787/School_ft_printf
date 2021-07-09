#include "ft_printf.h"

char			conv_num(unsigned int num, char type)
{
	char	numb;

	if ((num >= 1 && num <= 9) || num == 0)
		numb = num + '0';
	if (num > 9 && num <= 16 && type == 'x')
		numb = num + 'W';
	if (num > 9 && num <= 16 && type == 'X')
		numb = num + '7';
	return (numb);
}

char			*conv_to_hex(unsigned int num, char type, char *num_str)
{
	*num_str = '\0';
	if (num == 0)
		*--num_str = '0';
	while (num != 0)
	{
		*--num_str = conv_num(num % 16, type);
		num = num / 16;
	}
	return (num_str);
}

struct s_parser	ft_hex(va_list ap, struct s_parser pars)
{
	unsigned int	num;
	char			*num_str;
	char			*buf;

	num = va_arg(ap, unsigned int);
	if (num == 0 && pars.precision == 0)
		return (num0_prec0(pars));
	buf = (char *)malloc(9 * sizeof(char));
	if (!buf)
		return (pars = error(pars));
	num_str = &buf[8];
	num_str = conv_to_hex(num, pars.type, num_str);
	pars = compare_prec_and_width(pars, num_str);
	if (pars.flag < 2)
		pars = ft_di_flags_0_or_1(pars, num_str);
	if (pars.flag == 2)
		pars = ft_di_flag_2(pars, num_str);
	free_str(&buf);
	return (pars = clear_pars(pars));
}
