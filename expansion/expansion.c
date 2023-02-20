#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"
#include <stdlib.h>
#include <stdio.h>
#include "expansion.h"

char	*get_expanded_dollars(const char *token, const char **env_copy)
{
	t_position	index;
	char		*new_token;
	char		*new_token_tmp;

	index.start = 0;
	index.end = 0;
	new_token = NULL;

	new_token_tmp = ft_strdup((char *)token);
	if (new_token_tmp == NULL)
		return (NULL);
	while (get_var_position(index.end, new_token_tmp, &index.start, &index.end) == TRUE)
	{
		new_token = expand_dollar(new_token_tmp, env_copy, index);
		free(new_token_tmp);
		if (new_token == NULL)
		{
			// free new_token_tmp and more ?
			return (NULL);
		}
		new_token_tmp = new_token;
	}
	return (new_token);
}

char	*expand(const char *token, const char **env_copy)
{
	char	*expanded;

	expanded = get_expanded_dollars(token, (const char **)env_copy);


	// TODO si la variable n'existe pas, on enlever le $VAR
	if (expanded == NULL)
	{
		// TODO
		expanded = ft_strdup((char *)token);
		if (expanded == NULL)
			return (NULL);
	}
	//unquote(expanded);
	return (expanded);
}
