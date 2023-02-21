#ifndef PARSERANDEXECUTOR_H
#define PARSERANDEXECUTOR_H
#include <iostream>
#include <vector>

extern "C" {
#include "../parser/parser.h"
#include <string.h>
}

static char **setup_argv(std::vector<std::string> argv) {
  char **res = (char **)malloc(sizeof(char *) * (argv.size() + 1));
  for (int i = 0; i < argv.size(); i++)
    res[i] = strdup(argv[i].c_str());
  res[argv.size()] = NULL;
  return res;
}

static t_cmd *new_cmd(t_cmd_type type) {
  t_cmd *cmd = (t_cmd *)malloc(sizeof(t_cmd));
  cmd->type = type;
  cmd->cmd.heredoc = NULL;
  return cmd;
}

#endif /* PARSERANDEXECUTOR_H */
