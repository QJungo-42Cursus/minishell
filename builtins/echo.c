#include <stdio.h>
#include "../libft/libft.h"
#include <string.h>

int	echo(char **argv)
{
	t_bool	n_mode;
	int		i;

	i = 1;
	n_mode = (ft_strncmp(argv[i], "-n", 3) == 0);
	if (n_mode)
		i++;
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		if (argv[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (n_mode == FALSE)
		printf("\n");
	return (SUCCESS);
}

/*
int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)envp;
	echo(argv);
	return (0);
}
*/
