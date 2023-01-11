/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nb.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:43:51 by qjungo            #+#    #+#             */
/*   Updated: 2022/11/08 11:00:08 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NB_H
# define NB_H

char	*ft_itoa(int n);
int		ft_atoi(const char *string);
long	long_atoi(const char *string);
char	*utoa(unsigned int n);
char	*itoa_base(unsigned long long int n, char *base, unsigned int n_base);

#endif /* NB_H */
