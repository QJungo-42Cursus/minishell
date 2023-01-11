/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:42:52 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/14 20:20:27 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
# define STR_H
# include <stdlib.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	**ft_split(char const *s, char c);
char	**ft_split_pad(char const *s, char c, int padding);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(char *string);
int		ft_strlen(const char *string);
int		ft_strncmp(const char *str1, const char *str2, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
char	*ft_strrchr(char *str, int c);
char	*ft_strchr(char *str, int c);
void	strrev(char *string);
int		strlen_until(const char *string, const char *charset);
char	*char_to_str(char c);

#endif /* STR_H */
