#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "libft/libft.h"

struct			s_parser
{
	int			flag;
	int			width;
	int			precision;
	char		type;
	int			count;
	int			error;
	int			sign;
};

int				ft_printf(const char *format, ...);
struct s_parser	ft_di(va_list ap, struct s_parser pars);
struct s_parser	ft_c(va_list ap, struct s_parser pars);
struct s_parser	ft_s(va_list ap, struct s_parser pars);
struct s_parser	ft_hex(va_list ap, struct s_parser pars);
struct s_parser	ft_u(va_list ap, struct s_parser pars);
struct s_parser	ft_p(va_list ap, struct s_parser pars);
struct s_parser	ft_percent(struct s_parser pars);
struct s_parser	ft_di_flags_0_or_1(struct s_parser pars,
		char *num_str);
struct s_parser	ft_di_flag_2(struct s_parser pars,
		char *num_str);
struct s_parser	compare_prec_and_width(struct s_parser pars,
		char *num_str);
struct s_parser	num0_prec0(struct s_parser pars);
struct s_parser	clear_pars(struct s_parser pars);
struct s_parser	error(struct s_parser pars);
const char		*pass(const char *format, int number);
void			free_str(char **str);
#endif
