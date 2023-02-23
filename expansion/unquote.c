void	unquote(char *str)
{
	int		i;
	int		j;

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
