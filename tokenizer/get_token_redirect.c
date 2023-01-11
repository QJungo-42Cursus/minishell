// TODO les simplifier ensemble ??


void	get_token_pipe(const char *str, int *index, int *start, int *end) // TODO autre term tech ?
{
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] == '|')
		(*index)++;
	(*end) = (*index);
}

void	get_token_ampersant(const char *str, int *index, int *start, int *end) // TODO ortho
{
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] == '&')
		(*index)++;
	(*end) = (*index);
}

void	get_token_semicolumn(const char *str, int *index, int *start, int *end)
{
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] == ';')
		(*index)++;
	(*end) = (*index);
}

void	get_token_greater(const char *str, int *index, int *start, int *end)
{
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] == '>')
		(*index)++;
	(*end) = (*index);
}

void	get_token_less(const char *str, int *index, int *start, int *end)
{
	(*start) = *index;
	while (str[*index] != '\0' && str[*index] == '<')
		(*index)++;
	(*end) = (*index);
}
