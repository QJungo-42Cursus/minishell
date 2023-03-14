/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:02:34 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/12 14:43:20 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include "../minishell.h"
# include "../libft/libft.h"

void		expand(char **token, t_minishell *minishell);
void		unquote(char *str);
int			get_var_position(int begin_from,
				const char *token, int *start_index, int *end_index);
void		expand_and_retokenize(t_list **tokens, t_minishell *minishell);
//char		*expand_dollar(char *token,
				//t_minishell *minishell, t_position position);

#endif /* EXPANSION_H */
