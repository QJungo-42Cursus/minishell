/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:52:35 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/25 12:18:31 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_CHECKER_H
# define TOKEN_CHECKER_H
# include <stdio.h> 
# include <errno.h>
# include "../libft/libft.h"

int		check_valid_tokens(t_list *input_tooken);
int		get_first_occurence_in_list(t_list *lst, char *sep);
int		get_last_index_in_list(t_list *lst, int len, char *sep);
int		count_separateur_in_tooken(t_list *lst, char *sep);
int		count_separateur_in_tooken(t_list *lst, char *sep);
t_bool	are_two_pipe_consecutive(t_list *current);

#endif /* TOKEN_CHECKER_H */
