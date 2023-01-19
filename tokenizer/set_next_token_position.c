#include "tokenizer.h"
#include "../tests/debug_helper.h"

// !!!!! Le token comporte ses separateurs (ex: "echo salut" -> "echo salut", pas "echo salut" -> echo salut)
//		-> Ca permet a l'executeur de savoir si c'est des quotes ou des doubles quotes (pour les variables et les substitutions)
int	set_next_token_position(const char *cmd, int cursor_index, t_set_token_position *set_token_position, t_position *token_position)
/// Renvoie la position du prochain token qu'il se charge de trouver
{
	t_sep	separator;

	token_position->start = cursor_index;
	separator = get_sep(cmd[cursor_index]); // TODO get_sep => get_sep_from_cursor_first_char
	set_token_position[separator](cmd, cursor_index, token_position);
	// TODO il peut renvoyer une erreur quand il n'y a juste rien. pas ouf..
	if (token_position->start == -1 || token_position->end == token_position->start)// TODO ? || token_position->end == 0)
		return (ERROR);
	else
		return(SUCCESS);
}
