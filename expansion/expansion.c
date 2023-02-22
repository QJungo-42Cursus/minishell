#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"
#include <stdlib.h>
#include <stdio.h>
#include "expansion.h"

char	*get_expanded_dollars(const char *token, t_minishell *minishell)
{
	t_position	index;
	char		*new_token;
	char		*new_token_tmp;

	new_token = NULL;
	new_token_tmp = ft_strdup((char *)token);
	if (new_token_tmp == NULL)
		return (NULL);
	if (get_var_position(0, new_token_tmp, &index.start, &index.end) == FALSE)
	{
		free(new_token_tmp);
		return (ft_strdup((char *)token));
	}
	index.start = 0;
	index.end = 0;
	while (get_var_position(index.end, new_token_tmp, &index.start, &index.end) == TRUE)
	{
		new_token = expand_dollar(new_token_tmp, minishell, index);
		free(new_token_tmp);
		if (new_token == NULL)
		{
			free(new_token);
			return (NULL);
		}
		new_token_tmp = new_token;
	}
	return (new_token);
}

char	*expand(const char *token, t_minishell *minishell)
{
	char	*expanded;

	expanded = get_expanded_dollars(token, minishell);
	if (expanded == NULL)
	{
		// TODO
		expanded = ft_strdup((char *)token);
		if (expanded == NULL)
			return (NULL);
	}
	return (expanded);
}
