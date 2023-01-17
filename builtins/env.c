#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int env(t_minishell minishell)
{
	int		i;

	i = 0;
	while(minishell.env_copy[i] != NULL)
	{
		printf("minishell.env_copy[%d]: %s\n", i, minishell.env_copy[i]);
		i++;
	}
	return (SUCCESS);
}
