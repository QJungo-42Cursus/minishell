#include "../libft/libft.h"
#include <stdio.h>
#include "tokenizer.h"

void	log_tokens(t_list *tokens)
{
	while (tokens)
	{
		ft_printf("|%s| ", (char *)tokens->content);
		//ft_printf("\"%s\" ", (char *)tokens->content);
		tokens = tokens->next;
	}
}

void	log_sep(t_sep sep)
{
	if (sep == AMPERSAND)
		printf("AMPERSAND");
	else if (sep == PIPE)
		printf("PIPE");
	else if (sep == SEMICOLUMN)
		printf("SEMICOLON");
	else if (sep == LESS)
		printf("LESS");
	else if (sep == GREATER)
		printf("GREAT");
	else if (sep == QUOTE)
		printf("QUOTE");
	else if (sep == DQUOTE)
		printf("DQUOTE");
	else if (sep == BACKSLASH)
		printf("BACKSLASH");
	else if (sep == NONE)
		printf("NONE");
	else if (sep == SEP_ERROR)
		printf("ERROR");
	else
		printf("UNKNOWN");
	printf(" (%d)\n", sep);

}
