NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
INCLUDES =		-I$(HOME)/.brew/opt/readline/include
OUT_LIBS =		-L$(HOME)/.brew/opt/readline/lib \
				-lreadline
SRCS =			main.c			# Les bonnus (*, &&, ||) sont inclus dans le truc de base
OBJS =			$(SRCS:.c=.o)

.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
all: $(NAME)
$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(OUT_LIBS) $(LIBFT) -o $(NAME)

clean:
	@$(RM) $(OBJS)
	#@make clean -C libft

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
