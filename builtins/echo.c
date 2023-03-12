/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:00:51 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/12 18:44:20 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../libft/libft.h"
#include <string.h>

int	valid_flag(char *argument)
{
	int	i;

	if (argument[0] != '-')
		return (ERROR);
	i = 1;
	while (argument[i] && argument[i] == 'n')
		i++;
	if (argument[i] == '\0')
		return (SUCCESS);
	else
		return (ERROR);
}

int	echo(char **argv)
{
	t_bool	n_mode;
	int		i;

	if (argv[1] == NULL)
	{
		printf("\n");
		return (SUCCESS);
	}
	i = 1;
	while (argv[i] && valid_flag(argv[i]) == SUCCESS)
		i++;
	n_mode = (i != 1);
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
