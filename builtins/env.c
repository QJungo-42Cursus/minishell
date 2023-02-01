#include "../minishell.h"
#include "../libft/libft.h"
#include <stdio.h>

int env(t_minishell *minishell, char **argv)
{
	int		i;

	(void)argv; // TODO check args

	i = 0;
	while(minishell->env_copy[i] != NULL)
	{
		printf("%s\n", minishell->env_copy[i]);
		i++;
	}
	return (SUCCESS);
}
