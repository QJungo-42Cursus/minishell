#ifndef PARSER_H
# define PARSER_H

typedef enum e_type {
	COMMANDS,
	PIPELINE,

	COMMAND,

	CMD_SUFFIX,
	CMD_NAME,
	CMD_PREFIX,
}	t_type;

typedef struct s_node {
	t_type			type;
	void			*data;
	struct s_node	*next;
}	t_node;

/// COMMANDS
/// plusieurs commandes (separee par ; && ou ||) TODO comment diferencier les trois, avec un suffix ?
/// data contient un node de type COMMAND 
/// next contient le prochain node COMMANDS ou PIPELINE (pk il pourrait y avoir plusieur liste de commands ?)

/// PIPELINE
/// plusieurs commandes separee par un |
/// data contient un node de type COMMANDS
/// next contient le prochain node COMMANDS ou PIPELINE (pk il pourrait y avoir plusieur liste de commands ?)

/// COMMAND
/// une commande et tout ses pre/su-fixes
/// data contient un node de type CMD_PREFIX ou CMD_NAME
/// next contient le prochain node COMMAND

/// CMD_PREFIX
/// le suffix d'une commande (e.g. < file)
/// data contient un t_cmd_prefix
/// next contient le prochain node CMD_NAME
/// TODO est-ce qu'il ne peut y avoir qu'un seul prefix

/// CMD_NAME
/// le nom d'une commande
/// data contient un char* du nom de la commande
/// next contient le prochaine node CMD_SUFFIX

/// CMD_SUFFIX
/// le nom d'un suffix, ca peut etre un flag ou une redirection
/// data contient un char* du suffix
/// next contient le prochain suffix

typedef struct s_cmd_prefix {
	//
}	t_cmd_prefix;

#endif /* PARSER_H */
