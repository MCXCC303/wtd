#include "builtin.h"
#include <stdio.h>
#include <string.h>

static struct cmd_struct commands[] = {
    {"help", cmd_help},     {"init", cmd_init},       {"rename", cmd_rename},
    {"remove", cmd_remove}, {"show", cmd_show},       {"td", cmd_todo},
    {"type", cmd_type},     {"version", cmd_version},
};

int main(int argc, const char **argv) {
  if (argc == 1) {
    printf("%s%s", wtd_intro_string, wtd_usage_string);
    return 0;
  }
  if (argc >= 2) {
    if (!strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) {
      printf("%s%s", wtd_intro_string, wtd_usage_string);
      printf("\n%s", wtd_help_string);
      return 0;
    }
    if (!strcmp(argv[1], "-v") || !strcmp(argv[1], "--version")) {
      printf("%s", wtd_intro_string);
      printf("%s\n", WTD_VERSION);
      return 0;
    }
    if (parse_primary_command(argc, argv, commands) == INVALID_CMD) {
      if (argv[1][0] == '-') {
        printf("Invalid argument %s\n%s", argv[1], wtd_usage_string);
        return 0;
      } else {
        printf("Invalid command %s\n\n%s", argv[1], wtd_help_string);
        return 0;
      }
    }
  }
  return 0;
}
