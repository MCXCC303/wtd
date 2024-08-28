/*
  wtd version command

  Copyright (C) 2024 MCXCC
*/

#include "builtin.h"
#include <stdio.h>

int cmd_version(int argc, const char **argv) {
  printf("%s", wtd_intro_string);
  printf("%s\n", WTD_VERSION);
  return 0;
}