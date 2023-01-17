#ifndef AST_NODES_H
# define AST_NODES_H

/********************************** AST NODE **********************************/

typedef enum e_ast_node_type {
	COMMAND,
	PIPELINE,
	LOGICAL,
}	t_ast_node_type;


typedef struct s_extention {
	//t_position	*position; // TODO
	int		start;
	int		end;
	char	*value;
}	t_extention;


typedef struct s_ast_node {
	t_ast_node_type		type;
	char *				text;
	t_extention			*extention; // TODO pointeur ? (sinon bool is_extention)
}	t_ast_node;

/******************************* AST SPECIFIC NODES ***************************/

typedef struct s_ast_node_command {
	t_ast_node					*node;
	t_ast_node					*suffix;
	t_ast_node 					*prefix;
	struct s_ast_node_command	*next;
}	t_ast_node_command;

typedef struct s_ast_node_fix { // suffix and prefix (ltr)
	t_ast_node					*node;
	struct s_ast_node_xfix		*next;
}	t_ast_node_xfix;

typedef enum e_logical_type {
	AND,
	OR,
}	t_logical_type;

typedef struct s_ast_node_logical {
	t_ast_node					*node;
	t_logical_type				type;
	void						*left;
	void						*right;
}	t_ast_node_logical;

#endif /* AST_NODES_H */
/*
{
	"type": "Script",
		"commands": [
		{
			"type": "LogicalExpression",
			"op": "or",
			"left": {
				"type": "Subshell",
				"list": {
					"type": "CompoundList",
					"commands": [
					{
						"type": "LogicalExpression",
						"op": "and",
						"left": {
							"type": "Command",
							"name": {
								"text": "echo",
								"type": "Word"
							},
							"suffix": [
							{
								"text": "hello",
								"type": "Word"
							},
							{
								"text": "world",
								"type": "Word"
							}
							]
						},
						"right": {
							"type": "Command",
							"name": {
								"text": "s",
								"type": "Word"
							}
						}
					}
					]
				}
			},
			"right": {
				"type": "Command",
				"name": {
					"text": "echo",
					"type": "Word"
				}
			}
		}
	]
}
*/
