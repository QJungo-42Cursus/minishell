#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>



void	unquote(char *str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			i++;
		str[j] = str[i];
		i++;
		j++;
	}
	str[j] = '\0';
}

int	get_var_position(int begin_from, char *token, int *start_index, int *end_index)
{
	int		quoted;
	int		i;

	quoted = FALSE;
	i = begin_from;
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			quoted = !quoted;
		if (token[i] == '$' && !quoted)
		{
			*start_index = i;
			i++;
			while (token[i] != '\0' && is_in_charset(token[i], "$\'\" ") == FALSE)
				i++;
			*end_index = i - 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*get_expanded_dollar(char *token, char **env_copy)
{
	(void)env_copy;
	(void)token;
	return (NULL);
}


char	*expand(char *token, char **env_copy) // norm ?
{
	//char	*expanded = NULL;

	/*
	char	*unquoted = ft_strdup(token);
	unquote(unquoted);
	*/


	//return (unquoted);
	return (NULL);
}
