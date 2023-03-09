NAME =     		minishell
CC =			gcc
CFLAGS =		-Wall -Wextra -Werror
LIBFT =			-L./libft -lft
RM =			rm -f
SRCS =			main.c \
				minishell_utils.c \
				signal_handler.c \
				run_minishell.c \
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
				builtins/pwd.c \
				builtins/exit_.c \
				executor/executor.c \
				executor/executor_utils.c \
				executor/execute_pipeline.c \
				executor/execute_pipeline_utils.c \
				executor/execute_redir.c \
				executor/execute_command.c \
				executor/execute_builtin.c \
				parser/parser_utils.c \
				parser/parser_redir.c \
				parser/parse_command.c \
				parser/get_heredoc.c \
				parser/parse_pipeline.c \
				parser/parser.c \
				parser/free_ast.c \
				expansion/expansion.c \
				expansion/expend_dollar.c \
				expansion/unquote.c \
				expansion/expand_and_retokenize.c \
				expansion/get_var_position.c \
				token_checker/token_checker_main.c \
				token_checker/token_checker_utils.c
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

################################################ TESTS #########################
lldb: all
	lldb ./$(NAME)

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

san: all
	$(CC) $(CFLAGS) $(SAN) $(OUT_LIBS) $(INCLUDES) $(SRCS) $(LIBFT) -o $(NAME)


SRCS_TEST = tests/main.cpp \
			tests/tokenizer.cpp \
			tests/tokenizerWithQuote.cpp \
			tests/expansion.cpp \
			tests/executor.cpp \
			tests/builtins.cpp \
			tests/parser.cpp

#OBJS_TEST =		$(SRCS_TEST:.cpp=.o)
GTEST =		/usr/local/lib/libgtest.a $(OUT_LIBS)
ifeq ($(shell uname), Darwin)
GTEST_INC = -std=c++17 -I/Users/qjungo/.brew/include
GTEST =		/Users/qjungo/.brew/lib/libgtest.a
endif
NAME_TEST = test
LIBFT_A = ./libft/libft.a

# Attention, l'ordre de declaration des lib est important !
test:
	@make -C libft
	c++ $(GTEST_INC) $(SRCS_TEST) $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

ttok:
	@make -C libft
	c++ $(GTEST_INC) tests/main.cpp tests/tokenizer.cpp tests/tokenizerWithQuote.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

texp:
	@make -C libft
	c++ $(GTEST_INC) tests/main.cpp tests/expansion.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)

texec:
	@make -C libft
	c++ $(GTEST_INC) tests/main.cpp tests/executor.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST) 
	./$(NAME_TEST)
	
tbuil:
	@make -C libft
	c++ $(GTEST_INC)  tests/main.cpp tests/builtins.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST)
	./$(NAME_TEST)

tpars:
	@make -C libft
	c++ $(GTEST_INC)  tests/main.cpp tests/parser.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST)
	./$(NAME_TEST)

tend: $(OBJS)
	@make -C libft
	c++ $(GTEST_INC)  tests/end2end.cpp $(GTEST) $(LIBFT_A) -o $(NAME_TEST)
	./$(NAME_TEST)

#### Phony ####
.PHONY: all clean fclean re $(NAME_TEST)
