NAME =     		libft.a
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
RM =			rm -f

SRCS_STR =		ft_strmapi.c \
				ft_striteri.c \
				ft_strnstr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strdup.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strncmp.c \
				ft_strlcat.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_toupper.c \
				ft_tolower.c \
				ft_split.c \
				ft_split_pad.c \
				char_to_str.c \
				strlen_until.c \
				strrev.c

SRCS_NB = 		ft_itoa.c \
				ft_atoi.c \
				long_atoi.c \
				itoa_base.c \
				utoa.c

SRCS_CHAR = 	ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isspace.c \
				is_in_charset.c

SRCS_LST = 		ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstlast.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c

SRCS_PRT = 		ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putstr_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_color.c \
				ft_printf/ft_printf.c \
				ft_printf/conversions/conversions.c \
				ft_printf/conversions/character.c \
				ft_printf/conversions/hexa.c \
				ft_printf/conversions/pointer.c \
				ft_printf/writer/writer.c \
				ft_printf/writer/swriter.c \
				ft_printf/utils/free_join.c \
				ft_printf/utils/index_words.c

SRCS_MEM =		ft_calloc.c \
				ft_bzero.c \
				ft_memcpy.c \
				ft_memcmp.c \
				ft_memchr.c \
				ft_memset.c \
				ft_memmove.c \
				split_free.c

SRCS_MATH = 	geometrie/line.c \
				geometrie/translation.c \
				geometrie/map_op.c \
				geometrie/conversions.c \
				matrix/operations.c \
				matrix/conversions.c \
				matrix/new.c \
				vec/new.c \
				vec/copy.c \
				vec/conversions.c \
				vec/assert.c \
				abs.c \
				new_.c \
				ft_pow.c

SRCS_MLX = 		line.c \
				line.c \
				draw_line.c \
				draw_line_utils.c \
				pixel_to_image.c


SRCS = 			$(addprefix char/,	$(SRCS_CHAR)) \
				$(addprefix str/,	$(SRCS_STR)) \
				$(addprefix lst/,	$(SRCS_LST)) \
				$(addprefix mem/,	$(SRCS_MEM)) \
				$(addprefix nb/,	$(SRCS_NB)) \
				$(addprefix prt/,	$(SRCS_PRT)) \
				$(addprefix math/,	$(SRCS_MATH)) \
				$(addprefix mlx/,	$(SRCS_MLX)) \
				get_next_line.c

# TODO mettre le test_utils ailleurs pour y avoir acces plus facilement ?
SRCS_T =		test_printf.c \
				test_sprintf.c \
				test_utils.c \
				main.c

SRCS_TEST =		$(addprefix tests/,	$(SRCS_T))

OBJS =			$(SRCS:.c=.o)
OBJS_T =		$(SRCS_TEST:.c=.o)

$(NAME): $(OBJS)
	@ar -rcs $(NAME) $(OBJS)

all: $(NAME)

clean:
	@$(RM) $(OBJS) $(OBJS_T)
fclean: clean
	@$(RM) $(NAME) tester

re: fclean all

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

# TODO : garder ca tout le temps ?? (pour le san)
#%.o: %.c
#		@$(CC) -I. -o $@ -c $? $(SAN) $(CFLAGS)

test: $(OBJS) $(OBJS_T)
	ar -rcs $(NAME) $(OBJS)
	$(CC) $(CFLAGS) $(SAN) $(OBJS_T) -L. -lft -o tester
	./tester

.PHONY: all clean fclean re
