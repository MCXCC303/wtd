/*
  wtd type commands

  Copyright (C) 2024 MCXCC
*/

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static struct cmd_struct type_commands[] = {
    {"add", cmd_type_add},
    {"remove", cmd_type_remove},
    {"list", cmd_type_list},
};

const char *wtd_type_help_string = "Usage: \twtd type [-h | --help]\n\n"
                                   "or:\twtd type add [new type name]\n"
                                   "or:\twtd type list [-o | --oneline]\n"
                                   "or:\twtd type remove [type name]\n";

int cmd_type(int argc, const char **argv) {
  if (argv[2] == NULL || !strcmp(argv[2], "-h") || !strcmp(argv[2], "--help")) {
    printf("%s", wtd_type_help_string);
    return 0;
  }

  if (WTD_NOT_EXIST) {
    printf("No wtd detected.\nUse \"wtd init\" to create one first.\n");
    return 0;
  }

  if (parse_secondary_command(argc, argv, type_commands) == INVALID_CMD) {
    printf("Invalid %s %s\n\n%s", argv[2][0] == '-' ? "argument" : "command",
           argv[2], wtd_type_help_string);
    return 0;
  }
  return 0;
}

int cmd_type_add(int argc, const char **argv) {
  if (argv[3] == NULL) {
    printf("New type name needed.\n\n%s", wtd_type_help_string);
    return 0;
  }

  char new_type_file[MAX_WTD_NAME_LENGTH] = ".wtd/type/default.csv";
  replace_filename(new_type_file, "default", ".csv", argv[3]);
  if (detected_file(new_type_file)) {
    printf("wtd type %s already exists.\n"
           "Use \"wtd td [to-do name]\" to create a to-do in type \"%s\"\n",
           argv[3], argv[3]);
    return 0;
  }
  register_type(argv[3], REGISTER_ADD_TYPE);
  FILE *fp = fopen(new_type_file, "w+");
  fclose(fp);
  printf("Created new to-do type named \"%s\".\n", argv[3]);
  return 0;
}
int cmd_type_remove(int argc, const char **argv) {
  if (argv[3] == NULL) {
    printf("A type name needed.\n\n%s", wtd_type_help_string);
    return 0;
  }

  char remove_type_file[MAX_WTD_NAME_LENGTH] = ".wtd/type/default.csv";
  replace_filename(remove_type_file, "default", ".csv", argv[3]);
  if (detected_file(remove_type_file)) {
    printf("Detected wtd type \"%s\"\n"
           "Delete wtd type \"%s\"? (This will delete all to-do in type "
           "\"%s\") [y/N] ",
           argv[3], argv[3], argv[3]);
    if (getchar() == 'y') {
      register_type(argv[3], REGISTER_REMOVE_TYPE);
      remove(remove_type_file);
      printf("Removed wtd type \"%s\" successfully.\n", argv[3]);
      return 0;
    }
    printf("Aborted.\n");
    return 0;
  }
  printf("No wtd type named \"%s\"\n", argv[3]);
  return 0;
}
int cmd_type_list(int argc, const char **argv) {
  FILE *fp_type_list = fopen(".wtd/type/typelist", "r");
  printf("*** WTD TYPE LIST ***\n");
  char *type_name = malloc(sizeof(char) * MAX_WTD_NAME_LENGTH);
  while (fgets(type_name, MAX_WTD_NAME_LENGTH, fp_type_list) != NULL) {
    printf("%s", type_name);
  }
  fclose(fp_type_list);
  free(type_name);
  return 0;
}