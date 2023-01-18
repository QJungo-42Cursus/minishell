#include "../libft/libft.h"
#include "../minishell.h"
#include "../env/env.h"

int	add_env_var(t_minishell *mini, char *var)
{
	char	**new_env_copy;
	int		i;

	i = 0;
	// TODO function list len -> libft
	while (mini->env_copy[i] != NULL)
		i++;
	new_env_copy = malloc(sizeof(char *) * i + 1);
	if (new_env_copy == NULL)
		return (0);
	i = 0;
	while (mini->env_copy[i] != NULL)
	{
		new_env_copy[i] = mini->env_copy[i];
		i++;
	}
	new_env_copy[i] = var;
	new_env_copy[i + 1] = NULL;
	free(mini->env_copy);
	mini->env_copy = new_env_copy;
	return (SUCCESS);
}

static int	check_var_name(char *var)
{
	if(ft_strchr(var, '=') == NULL)
		return (ERROR);
	return (SUCCESS);
}

int	export_(t_minishell *minishell, char **argv)
{
	char	*var;
	int		var_index;

	if (check_var_name(argv[1]) == ERROR)
	{
		//TODO Message error
		return (ERROR);
	}
	var = ft_strdup(argv[1]);
	if (var == NULL)
		return (ERROR);
	var_index = env_var_index(minishell, var);
	if (var_index == -1)
	{
		if (add_env_var(minishell, var) == ERROR)
		{
			free(var);
			return (ERROR);
		}
	}
	else
	{
		free(minishell->env_copy[var_index]);
		minishell->env_copy[var_index] = var;
	}

	if (ft_strncmp(var, "PATH=", 5) == 0)
	{
		split_free(minishell->env_paths);
		minishell->env_paths = get_paths_in_env(minishell->env_copy);
		if (minishell->env_paths == NULL)
			return (ERROR); // TODO aie error handling
	}
	return (SUCCESS);
}
