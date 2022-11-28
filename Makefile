NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f

### MAAAC OS
INCLUDES =		-I$(HOME)/.brew/opt/readline/include
OUT_LIBS =		-L$(HOME)/.brew/opt/readline/lib \
				-lreadline
SRCS =			main.c			# Les bonnus (*, &&, ||) sont inclus dans le truc de base
OBJS =			$(SRCS:.c=.o)
.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
#####

CACA =			-lreadline

# Les bonnus (*, &&, ||) sont inclus dans le truc de base
SRCS =		main.c \
			tokenizer/tokenizer.c \
			tokenizer/get_next_token_functions.c \
			tokenizer/debug_helpers.c \
			tokenizer/get_token_normal.c \
			tokenizer/get_token_quote.c \
			tokenizer/get_token_dquote.c \
			tokenizer/get_token_redirect.c \
			builtins/echo.c

#SRCS =		main.c
OBJS =		$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(CACA) $(LIBFT) -o $(NAME)

all: $(NAME)
$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(OUT_LIBS) $(LIBFT) -o $(NAME)

clean:
	@make clean -C libft
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)
	#@make fclean -C libft

re: fclean all

### TESTS ###
u_libft:
	#rm -rf libft
	cp -r ../libft .
	rm -rf libft/.git

t: all
	./minishell

db:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./minishel 

.PHONY: all clean fclean re test libft
