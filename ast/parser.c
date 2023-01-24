#include <stdio.h>
#include "parser.h"
#include "../libft/libft.h"

t_cmd	*parser(t_list *tokens)
{
	t_list	*tok = tokens;

	while (tok->next != NULL)
	{
		printf("| %s |", (char *)tok->content);
	}
	return (NULL);
}



int	main()
{

}
