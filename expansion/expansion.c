#include "../minishell.h"
#include "../libft/libft.h"
#include "../env/env.h"
#include <stdlib.h>
#include <stdio.h>


// test covered
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

// test covered
int	get_var_position(int begin_from, const char *token, int *start_index, int *end_index)
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
			// TODO voire tout les separateurs
			while (token[i] != '\0' && is_in_charset(token[i], "$:\'\" ") == FALSE)
				i++;
			*end_index = i - 1;
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*expand_dollar(const char *token, const char **env_copy, int start_index, int end_index)
{
	char	*var_name;
	char	*var_value;
	char	*new_token_tmp;
	char	*new_token;

	//printf("Expand dollar -----\n");

	// get var name
	var_name = ft_substr(token, start_index + 1, end_index - start_index);
	if (var_name == NULL)
		return (NULL); // TODO
	//printf("var_name: %s\n", var_name);

	// get var value
	var_value = get_env_var_value(var_name, env_copy);
	free(var_name);
	if (var_value == NULL)
		return (NULL); // TODO
	//printf("var_value: %s\n", var_value);

	if (start_index == 0)
	{
		new_token_tmp = var_value;
	}
	else
	{
		// TODO free le substr
		new_token_tmp = ft_strjoin(ft_substr(token, 0, start_index), var_value);
		if (new_token_tmp == NULL)
			return (NULL); // TODO
		free(var_value);
	}
	if (end_index == ft_strlen(token) - 1)
	{
		new_token = new_token_tmp;
	}
	else
	{
		// TODO free le substr
		new_token = ft_strjoin(new_token_tmp, ft_substr(token, end_index + 1, ft_strlen(token) - end_index));
		if (new_token == NULL)
			return (NULL); // TODO
		free(new_token_tmp);
	}
	return (new_token);
}

char	*get_expanded_dollars(const char *token, const char **env_copy)
{
	int		start_index;
	int		end_index;
	char	*new_token;
	char	*new_token_tmp;


	start_index = 0;
	end_index = 0;
	new_token = NULL;

	new_token_tmp = ft_strdup((char *)token);
	if (new_token_tmp == NULL)
		return (NULL); // TODO
	//printf("new_token_tmp: |%s|\n", new_token_tmp);
	while (get_var_position(end_index, new_token_tmp, &start_index, &end_index) == TRUE)
	{
		//printf("start_index: %d, end_index: %d\n", start_index, end_index);
		new_token = expand_dollar(new_token_tmp, env_copy, start_index, end_index);
		free(new_token_tmp);
		if (new_token == NULL)
		{
			//printf("new_token is NULL\n");
			return (NULL); // TODO
		}
		new_token_tmp = new_token;
	}
	//printf("new_token_tmp: |%s|\n", new_token_tmp);
	//printf("new_token: |%s|\n", new_token);
	return (new_token);
}


// ne prend pas la propriété de token
char	*expand(char *token, char **env_copy) // norm ?
{
	char	*expanded;

	expanded = get_expanded_dollars(token, (const char **)env_copy);
	// TODO si la variable n'existe pas, on enlever le $VAR
	if (expanded == NULL)
	{
		// TODO
		expanded = ft_strdup(token);
		if (expanded == NULL)
			return (NULL);
	}
	//printf("expanded: |%s|\n", expanded);
	unquote(expanded);
	//printf("unquote: |%s|\n", expanded);
	return (expanded);
}
