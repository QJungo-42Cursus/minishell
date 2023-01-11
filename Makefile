NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f

### MAC OS
#INCLUDES =		-I$(HOME)/.brew/opt/readline/include
#OUT_LIBS =		-L$(HOME)/.brew/opt/readline/lib \
#				-lreadline
#.c.o:
#		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
#####

SRCS =		main.c \
			tokenizer/tokenizer.c \
			tokenizer/get_next_token_functions.c \
			tokenizer/debug_helpers.c \
			tokenizer/get_token_normal.c \
			tokenizer/get_token_quote.c \
			tokenizer/get_token_dquote.c \
			tokenizer/get_token_redirect.c \
			builtins/echo.c

OBJS =		$(SRCS:.c=.o)

all: $(NAME)
$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(OUT_LIBS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS)
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

### TESTS ###

SRCS_TEST = tests/main.cpp \
			tests/tokenizer.cpp
#OBJS_TEST =		$(SRCS_TEST:.cpp=.o)
GTEST =		/usr/local/lib/libgtest.a
NAME_TEST = test
LIBFT_A = ./libft/libft.a

# Attention, l'ordre de declaration des lib est important !
test:
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

u_libft:
	#rm -rf libft
	cp -r ../libft .
	rm -rf libft/.git

lldb:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./$(NAME)

.PHONY: all clean fclean re test u_libft
