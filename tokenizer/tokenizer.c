#include "tokenizer.h"
#include "../libft/libft.h"

void	log_tokens(t_list *tokens)
{
	while (tokens)
	{
		ft_printf("|%s| ", (char *)tokens->content);
		//ft_printf("\"%s\" ", (char *)tokens->content);
		tokens = tokens->next;
	}
}

char	*get_next_token(char *str, int *index)
{
	char		*token;
	int			start;
	t_sep		sep;
	t_get_token	*get_token;

	get_token = list_func();
	if (get_token == NULL)
	{
		// TODO
		return (NULL);
	}

	/// cut the space (ft_trim ?)
	while (ft_isspace(str[*index]) && str[*index] != '\0')
		(*index)++;

	
	/// agir en fonction du separateur/1er char
	sep = get_sep(str[*index]);
	get_token[sep](str, index);

	/// avance jusqu'au prochain sep
	start = *index;
	while (!ft_isspace(str[*index]) && str[*index] != '\0')
	{
		// TODO add le parsing des quotes
		(*index)++;
	}
	if ((*index) - start != 0)
		token = ft_substr(str, start, (*index) - start);
	free(get_token);
	return (token);
}

void	tokenize(char *line, int *index, t_list **tokens)
{
	char	*token;

	token = get_next_token(line, index);
	if (token == NULL)
	{
		// TODO
	}
	ft_lstadd_back(tokens, ft_lstnew(token));
	if (*index == ft_strlen(line))
		return ;
	tokenize(line, index, tokens);
}

t_list *tokenizer(char *str)
{
	(void)str;
	char	*line = "echo hello world \" \"";
	t_list	*tokens;
	int		index;

	index = 0;
	tokens = NULL;
	tokenize(line, &index, &tokens);
	log_tokens(tokens);
	return (tokens);
}
