/*
  wtd builtins

  Copyright (C) 2024 MCXCC
*/

#ifndef BUILTIN_H
#define BUILTIN_H

#include <string.h>
#include <time.h>
#include <unistd.h>

#define PRIMARY_CMD 1
#define SECONDARY_CMD 2
#define MAX_WTD_NAME_LENGTH 256
#define REGISTER_ADD_TYPE 'a'
#define REGISTER_REMOVE_TYPE 'r'
#define WTD_VERSION "v0.0.1"
#define INVALID_CMD NULL
#define WTD_NOT_EXIST !detected_file(".wtd/conf/wtd.cfg")
#define DETECTED_WTD detected_file(".wtd/conf/wtd.cfg")
#define SUCC_PARSED(X) !strcmp(cmd_set[i].cmd, argv[X])

extern const char *wtd_intro_string;
extern const char *wtd_usage_string;
extern const char *wtd_help_string;

struct tm *get_current_time();

time_t get_time_stamp();

struct cmd_struct {
  char *cmd;
  int (*fn)(int argc, const char **argv);
};

struct wtd_config {
  char *name;
  char *init_time;
  char *rename_time_latest;
}; // Unused

struct td_struct {
  struct tm *due_time_struct;
  time_t due_time_stamp;
  char *td_name;
  char *comment;
  char status;
};

// parser
struct cmd_struct *parse_primary_command(int argc, const char **argv,
                                         struct cmd_struct *cmd_set);

struct cmd_struct *parse_secondary_command(int argc, const char **argv,
                                           struct cmd_struct *cmd_set);

// Remove needs
void delete_directory(const char *path);

// Type add needs
void replace_filename(char *path, char *file_name, char *prefix,
                      const char *new_name);

int register_type(const char *type_name, char MODE);

char *get_wtd_name();

int detected_file(const char *path);

// Primary command sets
int cmd_config(int argc, const char **argv);
int cmd_help(int argc, const char **argv);
int cmd_init(int argc, const char **argv);
int cmd_rename(int argc, const char **argv);
int cmd_remove(int argc, const char **argv);
int cmd_td(int argc, const char **argv); //
int cmd_type(int argc, const char **argv);
int cmd_version(int argc, const char **argv);

// config command sets
int cmd_config_show(int argc, const char **argv);
int cmd_config_edit(int argc, const char **argv); //

// td command sets
int cmd_td_add(int argc, const char **argv);    //
int cmd_td_show(int argc, const char **argv);   //
int cmd_td_remove(int argc, const char **argv); //

// type command sets
int cmd_type_add(int argc, const char **argv);
int cmd_type_list(int argc, const char **argv);
int cmd_type_remove(int argc, const char **argv);

#endif // BUILTIN_H