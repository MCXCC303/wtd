#include "builtin.h"
#include <stdio.h>

int cmd_help(int argc, const char **argv) {
  printf("%s%s", wtd_intro_string, wtd_usage_string);
  printf("\n%s", wtd_help_string);
  return 0;
}