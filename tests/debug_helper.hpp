#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

/* DEBUG_HELPER
 *
 * this file is used to debug the functions with printf
 * it is not used in the final program
 *
 */

// #include "../libft/libft.h"
// #include "../tokenizer/tokenizer.h"
#include <stdio.h>

#define LOG(msg)                                                               \
  printf("in %s() at line %d: ", __func__, __LINE__);                          \
  printf(msg);                                                                 \
  printf("\n");

#define CRASH(msg)                                                             \
  LOG(msg);                                                                    \
  exit(1);

#define LOG_TOKEN(to_log_tokens)                                               \
  {                                                                            \
    if (ft_strlen((char *)to_log_tokens->content) == 0) {                      \
      printf("`(empty)` ");                                                    \
    } else {                                                                   \
      printf("`%s` ", (char *)to_log_tokens->content);                         \
    }                                                                          \
    fflush(stdout);                                                            \
  }

#define LOG_TOKENS(o_tokens)                                                   \
  {                                                                            \
    t_list *to_log_tokens = o_tokens;                                          \
    if (to_log_tokens == NULL) {                                               \
      printf("NULL\n");                                                        \
    }                                                                          \
    while (to_log_tokens) {                                                    \
      LOG_TOKEN(to_log_tokens);                                                \
      to_log_tokens = to_log_tokens->next;                                     \
    }                                                                          \
    printf("\n");                                                              \
  }

#define LOG_SEP(o_sep)                                                         \
  {                                                                            \
    int to_log_sep = o_sep;                                                    \
    if (to_log_sep == PIPELINE)                                                \
      printf("PIPE");                                                          \
    else if (to_log_sep == COMMAND)                                            \
      printf("COMMAND");                                                       \
    else if (to_log_sep == LOGIC_AND_deprecated)                               \
      printf("LOGIC_AND");                                                     \
    else if (to_log_sep == LOGIC_OR_deprecated)                                \
      printf("LOGIC_OR");                                                      \
    else if (to_log_sep == REDIR_IN)                                           \
      printf("REDIR_IN");                                                      \
    else if (to_log_sep == REDIR_OUT)                                          \
      printf("REDIR_OUT");                                                     \
    else if (to_log_sep == REDIR_APPEND)                                       \
      printf("REDIR_APPEND");                                                  \
    else if (to_log_sep == HEREDOC)                                            \
      printf("HEREDOC");                                                       \
    else                                                                       \
      printf("UNKNOWN");                                                       \
    printf(" (%d)\n", to_log_sep);                                             \
    fflush(stdout);                                                            \
  }

#define PRINT_TOKENS(tokens)                                                   \
  {                                                                            \
    t_list *dbh_cursor = tokens;                                               \
    printf("[");                                                               \
    while (dbg_cursor != NULL) {                                               \
      printf("%s, ", (char *)dbh_cursor->content);                             \
      dbh_cursor = dbh_cursor->next;                                           \
    }                                                                          \
    printf("]\n");                                                             \
  }

#endif /* DEBUG_HELPER_H */
