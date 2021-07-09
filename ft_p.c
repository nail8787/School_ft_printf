#include "ft_printf.h"

static char		conv_num(unsigned long int num)
{
	char	numb;

	if ((num >= 1 && num <= 9) || num == 0)
		numb = num + '0';
	if (num > 9 && num <= 16)
		numb = num + 'W';
	return (numb);
}

static char		*conv_ptr(unsigned long int num, char *num_str)
{
	*num_str = '\0';
	if (num == 0)
		*--num_str = '0';
	while (num != 0)
	{
		*--num_str = conv_num(num % 16);
		num = num / 16;
	}
	*--num_str = 'x';
	*--num_str = '0';
	return (num_str);
}

struct s_parser	ft_p(va_list ap, struct s_parser pars)
{
	unsigned long int	num;
	char				*num_str;
	char				*buf;

	num = va_arg(ap, uint64_t);
	buf = (char *)malloc(17 * sizeof(char));
	if (!buf)
		return (pars = error(pars));
	num_str = &buf[16];
	num_str = conv_ptr(num, num_str);
	pars.precision = 0;
	pars = compare_prec_and_width(pars, num_str);
	if (pars.flag < 2)
		pars = ft_di_flags_0_or_1(pars, num_str);
	if (pars.flag == 2)
		pars = ft_di_flag_2(pars, num_str);
	free_str(&buf);
	return (pars = clear_pars(pars));
}
