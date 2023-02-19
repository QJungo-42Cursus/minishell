#include "minishell.h"
#include "libft/libft.h"
#include <unistd.h>
#include "env/env.h"

int refresh_prompt(t_minishell *minishell)
{
	if (minishell->prompt_msg != NULL)
		free(minishell->prompt_msg);
	//minishell->prompt_msg = ft_strjoin(minishell->current_working_directory," ./minishell $>");
    minishell->prompt_msg = ft_sprintf("[msh %s]$ ",
           minishell->current_working_directory);
	if (minishell->prompt_msg == NULL)
        // TODO exit ?
		return (ERROR);
	return (SUCCESS);
}

int	init_minishell(t_minishell *minishell, char **envp)
{
	minishell->cmd_input = NULL;
	minishell->last_exit_status = 0;
	minishell->prompt_msg = NULL;
	if (getcwd(minishell->current_working_directory, MAX_PATH_LEN + 1) == NULL)
		return (ERROR);
	minishell->env_copy = cpy_envp(envp);
	if (minishell->env_copy == NULL)
		return (ERROR);
	minishell->env_paths = get_paths_in_env(envp);
	if (minishell->env_paths == NULL)
	{
		split_free(minishell->env_paths);
		return (ERROR);
	}
	refresh_prompt(minishell);
	if (!minishell->prompt_msg)
		return (ERROR);
	minishell->should_exit = FALSE;
	return (SUCCESS);
}
