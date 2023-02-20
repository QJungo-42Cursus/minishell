/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo.student@42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 10:44:07 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/02 15:50:17 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static int	read_line(int fd, char **cache, int count)
{
	char	buf[BUFFER_SIZE + 1];
	char	*old_cache;

	count = -2;
	while (count)
	{
		count = read(fd, buf, BUFFER_SIZE);
		if (count == -1 || count == 0)
			return (count);
		buf[count] = '\0';
		if (*cache == NULL)
			*cache = ft_strdup(buf);
		else
		{
			old_cache = *cache;
			*cache = ft_strjoin(*cache, buf);
			free(old_cache);
		}
		if (ft_strchr(*cache, '\n'))
			break ;
	}
	return (count);
}

static int	get_line(char **res, char **cache, int fd, int *fd_status)
{
	if (!(*cache == NULL || !ft_strchr(*cache, '\n')))
		return (0);
	*res = NULL;
	*fd_status = read_line(fd, &(*cache), 0);
	if (*fd_status == 0)
	{
		if (*cache == NULL)
			return (1);
		*res = ft_strdup(*cache);
		free(*cache);
		*cache = NULL;
		return (2);
	}
	else if (*fd_status == -1)
	{
		free(*cache);
		*cache = NULL;
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*cache = NULL;
	char		*res;
	char		*end;
	char		*old_cache;
	int			fd_status;

	if (get_line(&res, &cache, fd, &fd_status))
		return (res);
	if (ft_strchr(cache, '\n'))
	{
		res = ft_strdup(cache);
		end = ft_strchr(res, '\n') + 1;
		*end = '\0';
		old_cache = cache;
		cache = ft_strdup((ft_strchr(cache, '\n') + 1));
		free(old_cache);
		if (ft_strlen(cache) == 0)
		{
			free(cache);
			cache = NULL;
		}
		return (res);
	}
	return (NULL);
}

/* BONUS MODE
int	init_cache(char ***cache)
{
	int	i;

	i = 0;
	if (*cache == NULL)
	{
		*cache = malloc(sizeof(char *) * 11000);
		if (*cache == NULL)
			return (1);
		while (i < 11000)
		{
			(*cache)[i] = NULL;
			i++;
		}
	}
	return (0);
}

static void	free_cache(char ***cache, char **to_free)
{
	int	i;

	i = 0;
	if (*to_free != NULL)
	{
		free(*to_free);
		*to_free = NULL;
	}
	while (i > 11000)
	{
		if ((*cache)[i] != NULL)
		{
			free(*cache);
			break ;
		}
		i++;
	}
}

static int	read_line(int fd, char **cache, int count, int total_count)
{
	char	buf[BUFFER_SIZE + 1];
	char	*old_cache;

	count = -2;
	total_count = 0;
	while (count)
	{
		count = read(fd, buf, BUFFER_SIZE);
		total_count += count;
		if (count == -1)
			return (-1);
		if (count == 0 && total_count == 0)
			return (0);
		buf[count] = '\0';
		if (*cache == NULL)
			*cache = ft_strdup("");
		old_cache = *cache;
		*cache = ft_strjoin(*cache, buf);
		if (old_cache != NULL)
			free(old_cache);
		if (ft_strchr(*cache, '\n'))
			break ;
	}
	return (count);
}

static int	get_line(char **res, char ***cache, int fd)
{
	int		fd_status;

	if ((*cache)[fd] == NULL || !ft_strchr((*cache)[fd], '\n'))
	{
		*res = NULL;
		fd_status = read_line(fd, &((*cache)[fd]), 0, 0);
		if (fd_status == 0)
		{
			if ((*cache)[fd] == NULL)
				return (1);
			*res = ft_strdup((*cache)[fd]);
			free_cache(cache, &(*cache)[fd]);
			return (1);
		}
		else if (fd_status == -1)
		{
			free_cache(cache, &(*cache)[fd]);
			return (1);
		}
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	**cache = NULL;
	char		*res;
	char		*end;
	char		*old_cache;

	if (init_cache(&cache))
		return (NULL);
	if (get_line(&res, &cache, fd))
		return (res);
	if (ft_strchr(cache[fd], '\n'))
	{
		res = ft_strdup(cache[fd]);
		end = ft_strchr(res, '\n') + 1;
		*end = '\0';
		old_cache = cache[fd];
		cache[fd] = ft_strdup((ft_strchr(cache[fd], '\n') + 1));
		free_cache(&cache, &old_cache);
		return (res);
	}
	return (NULL);
}
*/
