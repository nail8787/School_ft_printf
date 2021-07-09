NAME = libftprintf.a

SRC = ft_printf.c ft_c.c ft_di.c ft_p.c ft_s.c ft_u.c ft_hex.c ft_percent.c \
	  ft_printf_utils.c
OBJ = $(SRC:.c=.o)
HEADER = ft_printf.h
LIBFT = ./libft/libft.a
CFLAGS = -Wall -Werror -Wextra -I./ -c

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c $(HEADER) $(LIBFT)
	gcc $(CFLAGS) $< -o $@

$(LIBFT):
	make -C ./libft/
	cp $(LIBFT) ./$(NAME)

clean:
	make clean -C ./libft/
	/bin/rm -f $(OBJ)

fclean: clean
	make fclean -C ./libft/
	/bin/rm -f $(NAME)

re: fclean all
