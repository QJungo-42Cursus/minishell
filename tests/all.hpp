#ifndef ALL_H
#define ALL_H

extern "C" {
#ifndef TEST
#define TEST
#endif

#include "../main.c"
#include "../minishell_utils.c"
#include "../token_checker/token_checker_main.c"
#include "../token_checker/token_checker_utils.c"

#include "../builtins/cd.c"
#include "../builtins/echo.c"
#include "../builtins/env.c"
#include "../builtins/exit_.c"
#include "../builtins/export.c"
#include "../builtins/pwd.c"
#include "../builtins/unset.c"

#include "../env/cpy_envp.c"
#include "../env/find_command_path.c"
#include "../env/get_env_var_index.c"
#include "../env/get_env_var_value.c"
#include "../env/get_paths_in_env.c"

#include "../executor/execute_pipeline.c"
#include "../executor/execute_pipeline_utils.c"
#include "../executor/executor.c"
#include "../executor/execute_command.c"
#include "../executor/execute_builtin.c"
#include "../executor/executor_utils.c"
#include "../executor/execute_redir.c"

#include "../parser/parse_command.c"
#include "../parser/parse_pipeline.c"
#include "../parser/parse_redir.c"
#include "../parser/parse_redir_open.c"
#include "../parser/parser.c"
#include "../parser/free_ast.c"
#include "../parser/parser_utils.c"
#include "../parser/get_heredoc.c"

#include "../tokenizer/set_next_token_position.c"
#include "../tokenizer/tokenizer.c"

#include "../expansion/expansion.c"
#include "../expansion/get_var_position.c"
#include "../expansion/unquote.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
}

#endif /* ALL_H */
