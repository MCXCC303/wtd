#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>

struct cmd_struct config_commands[] = {
    {"show", cmd_config_show},
    {"edit", cmd_config_edit},
};

const char *wtd_config_help_string =
    "Usage: \twtd config [-h | --help]\n\n"
    "or:\twtd config show [-a | --all] [name]\n"
    "or:\twtd config edit [name] [param]\n";

int cmd_config(int argc, const char **argv) {
  if (argv[2] == NULL || !strcmp(argv[2], "-h") || !strcmp(argv[2], "--help")) {
    printf("%s", wtd_config_help_string);
    return 0;
  }

  if (WTD_NOT_EXIST) {
    printf("No wtd detected.\nUse \"wtd init\" to create one first.\n");
    return 0;
  }

  if (parse_secondary_command(argc, argv, config_commands) == INVALID_CMD) {
    printf("Invalid %s %s\n\n%s", argv[2][0] == '-' ? "argument" : "command",
           argv[2], wtd_config_help_string);
    return 0;
  }
  return 0;
}

int cmd_config_show(int argc, const char **argv) {
  system("vim -R .wtd/conf/wtd.cfg");
  return 0;
}

int cmd_config_edit(int argc, const char **argv) { return 0; } //