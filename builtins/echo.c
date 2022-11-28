#include <stdio.h>
#include "../libft/libft.h"

// TODO est-ce que le argv[0] doit contenir le nom echo dans ce cas ??
// Est-ce qu'on gere la transformation en varriable ici ? (je dirait non)
int	echo(char **argv /*, char **envp*/)
{
	t_bool	n_mode;
	int		i;

	if (argv == NULL)
	{
		// TODO
		return (ERROR);
	}
	if (*argv == NULL)
	{
		// TODO
		return (ERROR);
	}
	if (ft_strlen(*argv) == 2 && ft_strncmp(*argv, "-n", 2) == 0)
	{
		n_mode = TRUE;
		argv++;
	}
	else
	{
		n_mode = FALSE;
	}
	

	i = 0;
	while (argv[i] != NULL)
	{
		printf("%s", argv[i]);
		i++;
	}
	if (n_mode == FALSE)
		printf("\n");
	return (SUCCESS);
}
