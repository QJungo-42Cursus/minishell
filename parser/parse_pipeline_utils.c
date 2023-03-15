/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipeline_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qjungo <qjungo@student.42lausanne.ch>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 11:54:11 by qjungo            #+#    #+#             */
/*   Updated: 2023/03/15 11:54:18 by qjungo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parser.h"
#include "../builtins/builtins.h"

t_bool	is_pipe_alone(t_list *tokens)
{
	t_list		*cursor;

	cursor = tokens;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) != PIPELINE)
			return (FALSE);
		cursor = cursor->next;
	}
	cursor = tokens;
	while (cursor != NULL)
	{
		free(cursor->content);
		cursor = cursor->next;
	}
	return (TRUE);
}
