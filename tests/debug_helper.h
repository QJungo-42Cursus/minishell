#ifndef DEBUG_HELPER_H
#define DEBUG_HELPER_H

/* DEBUG_HELPER
 *
 * this file is used to debug the functions with printf
 * it is not used in the final program
 *
 */

//#include "../libft/libft.h"
//#include "../tokenizer/tokenizer.h"
#include <stdio.h>

#define LOG(msg)                                                               \
  printf("in %s() at line %d: ", __func__, __LINE__);                          \
  printf(msg);                                                                 \
  printf("\n");

#define CRASH(msg)                                                             \
  LOG(msg);                                                                    \
  exit(1);

#define LOG_TOKENS(o_tokens)                                                   \
  {                                                                            \
    /* printf("%d el in list\n", ft_lstsize(tokens));*/                        \
    t_list *to_log_tokens = o_tokens;                                          \
    while (to_log_tokens) {                                                    \
      printf("|%s| ", (char *)to_log_tokens->content);                         \
      fflush(stdout);                                                          \
      to_log_tokens = to_log_tokens->next;                                     \
    }                                                                          \
    printf("\n");                                                              \
  }

#define LOG_SEP(o_sep)                                                         \
  {                                                                            \
    t_sep to_log_sep = o_sep;                                                  \
    if (to_log_sep == AMPERSAND)                                               \
      printf("AMPERSAND");                                                     \
    else if (to_log_sep == PIPE)                                               \
      printf("PIPE");                                                          \
    else if (to_log_sep == SEMICOLUMN)                                         \
      printf("SEMICOLON");                                                     \
    else if (to_log_sep == LESS)                                               \
      printf("LESS");                                                          \
    else if (to_log_sep == GREATER)                                            \
      printf("GREAT");                                                         \
    else if (to_log_sep == QUOTE)                                              \
      printf("QUOTE");                                                         \
    else if (to_log_sep == DQUOTE)                                             \
      printf("DQUOTE");                                                        \
    else if (to_log_sep == BACKSLASH)                                          \
      printf("BACKSLASH");                                                     \
    else if (to_log_sep == NONE)                                               \
      printf("NONE");                                                          \
    else if (to_log_sep == SEP_ERROR)                                          \
      printf("ERROR");                                                         \
    else                                                                       \
      printf("UNKNOWN???");                                                    \
                                                                               \
    printf(" (%d)\n", to_log_sep);                                             \
    fflush(stdout);                                                            \
  }

#endif /* DEBUG_HELPER_H */
