#include "../libft/libft.h"
#include "expansion.h"
#include "../env/env.h"

static char *get_var_value(const char *token, const char **env_copy, t_position index)
{
	char		*var_name;
	char		*var_value;

	var_name = ft_substr(token, index.start + 1, index.end - index.start);
	if (var_name == NULL)
		return (NULL);
	if (get_env_var_index((const char **)env_copy, var_name) == -1)
		var_value = ft_strdup((char *)"");
	else
		var_value = get_env_var_value(var_name, env_copy);
	free(var_name);
	return (var_value);
}

static int	set_sides(const char *token, t_position index, char **a, char **b)
{
	if (index.start == 0)
		*a = ft_strdup((char *)"");
	else
		*a = ft_substr(token, 0, index.start);
	if (a == NULL)
		return (ERROR);
	*b = ft_substr(token, index.end + 1, ft_strlen(token) - index.end);
	if (b == NULL)
	{
		free(*a);
		return (ERROR);
	}
	return (SUCCESS);
}

char	*expand_dollar(const char *token, const char **env_copy, t_position index)
{
	char	*var_value;
	char	*a;
	char	*new_token;
	char	*b;

	var_value = get_var_value(token, env_copy, index);
	if (var_value == NULL)
		return (NULL);
	if (set_sides(token, index, &a, &b) == ERROR)
	{
		free(var_value);
		return (NULL);
	}
	new_token = ft_sprintf("%s%s%s", a, var_value, b);
	free(a);
	free(b);
	free(var_value);
	return (new_token);
}
