NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
SRCS =			main.c \
				tokenizer/tokenizer.c \
				tokenizer/get_next_token_functions.c \
				tokenizer/get_token_normal.c \
				tokenizer/get_token_quote.c \
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
				builtins/cd.c
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
			tests/executor.cpp

#OBJS_TEST =		$(SRCS_TEST:.cpp=.o)
GTEST =		/usr/local/lib/libgtest.a
NAME_TEST = test
LIBFT_A = ./libft/libft.a

# Attention, l'ordre de declaration des lib est important !
test:
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

tquote:
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*TokenizeWithQuote.*"

texp:
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Expansion*"

tpipe:
	c++ $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Pipeline.*"

texec:
	c++ tests/main.cpp tests/executor.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST) "--gtest_filter=*Executor*"

u_libft:
	#rm -rf libft
	cp -r ../libft .
	rm -rf libft/.git

lldb:
	@make -C libft
	@$(CC) $(CFLAGS) $(SRCS) -g $(LIBFT) -o $(NAME)
	lldb ./$(NAME)

#### Phony ####
.PHONY: all clean fclean re test u_libft
