/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 20:17:49 by qjungo            #+#    #+#             */
/*   Updated: 2023/02/24 20:26:47 by agonelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H
# include "../libft/libft.h"
# include "../minishell.h"

int			tokenizer(const char *cmd, t_list **tokens, t_bool is_expand_mode,
				t_minishell *minishell);
void		set_next_token_position(const char *cmd, int cursor_index,
				t_position *token_position,
				t_bool is_expand_mode);

#endif /* TOKENIZER_H */
