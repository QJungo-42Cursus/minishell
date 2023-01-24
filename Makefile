NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
SRCS =			main.c \
				tokenizer/tokenizer.c \
				tokenizer/set_next_token_position.c \
				env/cpy_envp.c \
				env/get_paths_in_env.c \
				env/get_env_var_index.c \
				env/get_env_var_value.c \
				env/find_command_path.c \
				builtins/echo.c \
				builtins/export.c \
				builtins/env.c \
				builtins/unset.c \
				builtins/cd.c \
				parser/parser_utils.c \
				parser/parse_command.c \
				parser/parser.c
OBJS =			$(SRCS:.c=.o)

#### INCLUDES (READLINE) ####
OUT_LIBS = -lreadline

ifeq ($(shell uname), Darwin) # MAC need the path to it (including the headers)
OUT_LIBS += -L$(HOME)/.brew/opt/readline/lib
INCLUDES = -I$(HOME)/.brew/opt/readline/include
.c.o:
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $(<:.c=.o)
endif

#### MAIN RULES ####
all: $(NAME)
$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) $(OUT_LIBS) $(LIBFT) -o $(NAME)

clean:
	$(RM) $(OBJS) test
	make clean -C libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C libft

re: fclean all

#### TESTS ####
SRCS_TEST = tests/main.cpp \
			tests/tokenizer.cpp \
			tests/tokenizerWithQuote.cpp \
			tests/expansion.cpp \
			tests/executor.cpp \
			tests/parser.cpp

#OBJS_TEST =		$(SRCS_TEST:.cpp=.o)
GTEST =		/usr/local/lib/libgtest.a
NAME_TEST = test
LIBFT_A = ./libft/libft.a

# Attention, l'ordre de declaration des lib est important !
test:
	@make -C libft
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

ttok:
	@make -C libft
	c++ tests/main.cpp tests/tokenizer.cpp tests/tokenizerWithQuote.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Tokenize*"

texp:
	@make -C libft
	c++ tests/main.cpp tests/expansion.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Expansion*"

texec:
	@make -C libft
	c++ tests/main.cpp tests/executor.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Executor*"

tpars:
	@make -C libft
	c++ tests/main.cpp tests/parser.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST)
	./$(NAME_TEST) "--gtest_filter=*Parser*"

#### Phony ####
.PHONY: all clean fclean re $(NAME_TEST)
