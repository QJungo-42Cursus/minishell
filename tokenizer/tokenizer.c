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

	/// Set le debut du token a l'index courant de la chaine
	start = *index;
	
	/// agit en fonction du separateur/1er char
	sep = get_sep(str[*index]);
	if (sep != NONE && sep != SEP_ERROR)
		get_token[sep](str, index, &start); // TODO rename get_token to set_indexes

	/// avance jusqu'au prochain sep
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
		ft_lstclear(tokens, free);
	}
	ft_lstadd_back(tokens, ft_lstnew(token));
	if (*index == ft_strlen(line))
		return ;
	tokenize(line, index, tokens);
}

t_list *tokenizer(char *str)
{
	t_list	*tokens;
	int		index;

	index = 0;
	tokens = NULL;
	tokenize(str, &index, &tokens);
	log_tokens(tokens);
	return (tokens);
}
