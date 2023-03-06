#include "../libft/libft.h"
#include <stdio.h>

void	iunquote(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	printf("before: |%s|\n", str);
	while (str[i] != '\0')
	{
		printf("%d -> %c \t\t", i, str[i]);
		if (is_in_charset(str[i], "\'\""))
			i++;
		if (str[i] == '\0')
			break ;
		str[j] = str[i];
		printf("%d -> %c \n", i, str[i]);
		i++;
		j++;
	}
	str[j] = '\0';
	printf("unquoted: |%s|\n\n", str);
}


char	set_sep(char c)
{
	if (is_in_charset(c, "\'\""))
	{
		printf("ptn de sep |%c|\n", c);
		return (c);
	}
	return (0);
}

t_bool	move_cursor(int *i, int *j, char *str, char *sep)
{
	while (str[*i] != '\0' && !is_in_charset(str[*i], "\'\""))
	{
		(*i)++;
		(*j)++;
	}
	*sep = set_sep(str[*i]);
	if (ft_strlen(str) == *i)
		return ((t_bool)TRUE);
	(*i)++;
	return ((t_bool)FALSE);
}

void	unquote(char *str)
{
	int		i;
	int		j;
	char	sep;

	i = 0;
	j = 0;
	if (move_cursor(&i, &j, str, &sep))
		return ;
	if (str[i] == sep)
	{
		printf("consssss\n");
		ft_memmove(&str[i - 1], &str[i + 1], ft_strlen(&str[i + 1]) + 1);
		unquote(&str[i - 1]);
		return ;

	}

	while (str[i] != '\0')
	{
		if (str[i] == sep)
		{
			printf("in: %s\n\n", &str[i]);
			unquote(&str[i]);
			return ;
		}
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
	printf("unquoted: |%s|\n\n", str);
}
