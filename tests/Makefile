NAME =     	tests_out
CC =		c++
#CFLAGS =	-Wall -Wextra -Werror 
RM =		rm -f
GTEST =		/usr/local/lib/libgtest.a
LIBFT =		-L. -lft

TEST_SRCS =	main.cpp \
			parser.cpp \
			tokenizer.cpp

SRCS =		../tokenizer/tokenizer.c \
			../tokenizer/get_next_token_functions.c \
			../tokenizer/debug_helpers.c \
			../tokenizer/get_token_normal.c \
			../tokenizer/get_token_quote.c \
			../tokenizer/get_token_dquote.c \
			../tokenizer/get_token_redirect.c \
			../builtins/echo.c

%.o: %.cpp Makefile
	$(CC) $(CFLAGS) -c $< -o $@

OBJS =		$(SRCS:.cpp=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(NAME)

$(NAME): build
	./$(NAME)

build: $(OBJS) $(TEST_OBJS)
	@make -C ../libft
	cp ../libft/libft.a .
	@$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJS) $(LIBFT) -o $(NAME) $(GTEST)

clean:
	@$(RM) $(OBJS) $(TEST_OBJS)

fclean: clean
	@$(RM) $(NAME) libft.a

re: fclean build

#### Specific tests ####
# STL
vector: build
	./$(NAME) "--gtest_filter=*VectorTest.*"


.PHONY: all clean fclean re build
