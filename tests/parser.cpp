#include "gtest/gtest.h"
#include <fstream>
#include <iostream>
#include <vector>


enum e_token_type {
  OPEN_PARENTHESES = 7,
  CLOSE_PARENTHESES = 8,
};


extern "C" {
#include "../ast/parser.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>

void print_token_type(int token_type) {
  if (token_type == OPEN_PARENTHESES)
    std::cout << "OPEN_PARENTHESES" << std::endl;
  else if (token_type == CLOSE_PARENTHESES)
    std::cout << "CLOSE_PARENTHESES" << std::endl;
  else if (token_type == PIPELINE)
    std::cout << "PIPE" << std::endl;
  else if (token_type == LOGIC_AND)
    std::cout << "AND" << std::endl;
  else if (token_type == LOGIC_OR)
    std::cout << "OR" << std::endl;
  else if (token_type == REDIR_IN)
    std::cout << "REDIRECT_IN" << std::endl;
  else if (token_type == REDIR_OUT)
    std::cout << "REDIRECT_OUT" << std::endl;
  else if (token_type == REDIR_APPEND)
    std::cout << "REDIRECT_APPEND" << std::endl;
  else if (token_type == COMMAND)
    std::cout << "WORD" << std::endl;
}

int get_token_type(char *token) {
  if (ft_strncmp(token, "(", 2) == 0)
    return OPEN_PARENTHESES;
  else if (ft_strncmp(token, ")", 2) == 0)
    return CLOSE_PARENTHESES;
  else if (ft_strncmp(token, "&&", 3) == 0)
    return LOGIC_AND;
  else if (ft_strncmp(token, "||", 3) == 0)
    return LOGIC_OR;
  else if (ft_strncmp(token, "|", 2) == 0)
    return PIPELINE;
  else if (ft_strncmp(token, ">>", 3) == 0)
    return REDIR_APPEND;
  else if (ft_strncmp(token, "<", 2) == 0)
    return REDIR_IN;
  else if (ft_strncmp(token, ">", 2) == 0)
    return REDIR_OUT;
  else
    return COMMAND;
}

t_bool	are_we_in_parentheses(t_list *tokens)
{
	t_list		*cursor;
	int			parentheses;

	cursor = tokens;
	parentheses = 0;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
			parentheses++;
		else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
			parentheses--;
		if (parentheses == 0 && cursor->next == NULL)
			return (TRUE);
		cursor = cursor->next;
	}
	return (FALSE);
}

t_list	*skip_parentheses(t_list *cursor)
{
	int			parentheses;

	parentheses = 0;
	if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
	{
		parentheses++;
		while (parentheses > 0)
		{
			cursor = cursor->next;
			if (get_token_type((char *)cursor->content) == OPEN_PARENTHESES)
				parentheses++;
			else if (get_token_type((char *)cursor->content) == CLOSE_PARENTHESES)
				parentheses--;
		}
	}
	return (cursor);
}

/* TODO une idee pour pouvoir tout free a la fin : faire une list de t_list, 
 *		bien garder la taille, et free tout les elements qui ne sont pas NULL
 *		- en cas d'erreur : tout free
 *		- reussite : ne free que les t_list et pas les strings 
 */
void	set_command(t_list *tokens, t_cmd *cmd)
{
	t_list		*cursor;
	t_list		*start_left;
	t_list		*start_right;
	int			tok_type;

	if (are_we_in_parentheses(tokens))
	{
		/* une sorte de "trim", ca enleve le debut et la fin de la t_list */
		cursor = tokens;
		while (cursor->next->next != NULL)
			cursor = cursor->next;
		free(cursor->next->content);
		free(cursor->next);
		cursor->next = NULL;
		cursor = tokens->next;
		free(tokens->content);
		free(tokens);
		tokens = cursor;
	}

	start_left = cursor;

	/* premiere passe qui cherche les LOGIC */
	while (cursor->next != NULL)
	{
		cursor = skip_parentheses(cursor);

		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == LOGIC_OR || tok_type == LOGIC_AND)
		{
			start_right = cursor->next->next;
			free(cursor->next->content);
			cursor->next = NULL;

			cmd->type = (t_cmd_type)tok_type;
			cmd->logic.left = (t_cmd *)malloc(sizeof(t_cmd));
			cmd->logic.right = (t_cmd *)malloc(sizeof(t_cmd));
			set_command(start_left, cmd->logic.left);
			set_command(start_right, cmd->logic.right);
			return ;
		}
		cursor = cursor->next;
	} // si on arrive a la fin de la boucle, c'est qu'il n'y a plus de &&,||

	/* deuxieme passe pour les redirections */
	cursor = tokens;
	while (cursor->next != NULL)
	{
		cursor = skip_parentheses(cursor);

		tok_type = get_token_type((char *)cursor->next->content);
		if (tok_type == REDIR_IN || tok_type == REDIR_OUT) // TODO dabors le out ? (ca devrait etre egal...)
		{
			cmd->type = (t_cmd_type)tok_type;
			cmd->redir.filename = (char *)cursor->next->next->content;
			/* saute le `> file`, donc 2 tokens */
			cursor->next = cursor->next->next->next;
			set_command(tokens, cmd->redir.cmd);
			return ;
		}
		cursor = cursor->next;
	} // si on arrive a la fin de la boucle, c'est qu'il n'y a plus de <, >
	
	/* 3eme passe, pipelines and simple cmd */
	cursor = tokens;
	// 1. check if pipeline or simple cmd
	t_bool	is_pipeline = FALSE;
	while (cursor != NULL)
	{
		if (get_token_type((char *)cursor->content) == PIPELINE)
		{
			is_pipeline = TRUE;
			break;
		}
		cursor = cursor->next;
	}
	// 2. ...
	if (is_pipeline)
	{
		cmd->type = PIPELINE;
		t_list	*start_argv = tokens;
		/* get argc len */
		int	argc = 0;
		cursor = tokens;
		while (cursor != NULL && get_token_type((char *)cursor->content) != PIPELINE)
		{
			cursor = cursor->next;
			argc++;
		}
	}
}

t_cmd *parser(t_list *tokens) {
	t_cmd	*cmd = (t_cmd*)malloc(sizeof(t_cmd *));
	return (cmd);
}
}

/*









*/

void testParser(std::vector<std::string> tokens) {
  t_list *tok = NULL;
  t_cmd *cmd = NULL;

  for (std::vector<std::string>::iterator it = tokens.begin();
       it != tokens.end(); ++it) {
    ft_lstadd_back(&tok, ft_lstnew(ft_strdup((char *)it->c_str())));
  }
  cmd = parser(tok);
}

int main(int argc, char **argv) { //
  testParser({"ls", "-l", "&&", "(", "echo", "hello", ")", "|", "cat", "-e"});
}

// TEST(d, d) {}
