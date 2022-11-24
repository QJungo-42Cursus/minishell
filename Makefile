NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
CACA =			-lreadline

# Les bonnus (*, &&, ||) sont inclus dans le truc de base
SRCS =		main.c \
			tokenizer/tokenizer.c \
			tokenizer/get_next_token_functions.c

#SRCS =		main.c
OBJS =		$(SRCS:.c=.o)

$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

all: $(NAME)

u_libft:
	rm -rf libft
	cp -r ../libft .
	rm -rf libft/.git


clean:
	@make clean -C libft
	@$(RM) $(S_OBJS) $(M_OBJS)

fclean: clean
	@make fclean -C libft
	@$(RM) $(NAME)

re: u_libft fclean all

### TESTS ###
t: all
	./minishell

db:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./minishel 

.PHONY: all clean fclean re test libft
