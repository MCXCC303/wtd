/*
  wtd parser

  Copyright (C) 2024 MCXCC
*/

#include "builtin.h"

struct cmd_struct *parse_primary_command(int argc, const char **argv,
                                         struct cmd_struct *cmd_set) {
  for (int i = 0; cmd_set[i].cmd; i++) {
    if (SUCC_PARSED(PRIMARY_CMD)) {
      cmd_set[i].fn(argc, argv);
      return &cmd_set[i];
    }
  }
  return INVALID_CMD;
}

struct cmd_struct *parse_secondary_command(int argc, const char **argv,
                                           struct cmd_struct *cmd_set) {
  for (int i = 0; cmd_set[i].cmd; i++) {
    if (SUCC_PARSED(SECONDARY_CMD)) {
      cmd_set[i].fn(argc, argv);
      return &cmd_set[i];
    }
  }
  return INVALID_CMD;
}