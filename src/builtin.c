/*
  wtd builtins

  Copyright (C) 2024 MCXCC
*/

#include "builtin.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

const char *wtd_intro_string = "wtd -- What To Do\n";
const char *wtd_usage_string = "Usage: wtd [-h | --help] [-v | --version]\n";
const char *wtd_help_string =
    "Commands:\n"
    "\tconfig\t\tshow and modify wtd config\n"
    "\thelp\t\tsee wtd helps\n"
    "\tinit\t\tinitiate a to-do list\n"
    "\trename\t\trename current to-do list\n"
    "\tremove\t\tremove current to-do list\n"
    "\ttype\t\tshow and modify to-do types in typelist\n"
    "\ttd\t\tshow and modify to-do list\n"
    "\tversion\t\tshow wtd version\n";

struct tm *get_current_time() {
  time_t tp = time(NULL);
  struct tm *time_struct;
  time_struct = localtime(&tp);
  time_struct->tm_year += 1900;
  time_struct->tm_mon += 1;
  return time_struct;
}

time_t get_time_stamp() { return time(NULL); }

char *get_wtd_name() {
  char *wtd_name = malloc(sizeof(char) * MAX_WTD_NAME_LENGTH);
  FILE *fp = fopen(".wtd/conf/wtd.cfg", "r");
  fscanf(fp, "name=%s", (char *)wtd_name);
  fclose(fp);
  return wtd_name;
}

void delete_directory(const char *path) {
  DIR *dir = opendir(path);
  struct dirent *entry;
  while ((entry = readdir(dir)) != NULL) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
    if (entry->d_type == DT_DIR) {
      if (strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")) {
        delete_directory(full_path);
      }
    } else {
      remove(full_path);
    }
  }
  closedir(dir);
  rmdir(path);
}

int detected_file(const char *path) { return !access(path, F_OK); }

void replace_filename(char *path, char *file_name, char *prefix,
                      const char *new_name) {
  *strstr(path, file_name) = '\0';
  char *fullName = malloc(sizeof(char) * strlen(new_name));
  strcpy(fullName, new_name);
  strcat(fullName, prefix);
  strcat(path, fullName);
  free(fullName);
}

int register_type(const char *type_name, char MODE) {
  if (MODE == REGISTER_ADD_TYPE) {
    rename(".wtd/type/typelist", ".wtd/type/typelist.old");
    FILE *fp_type_list_old = fopen(".wtd/type/typelist.old", "r");
    FILE *fp_type_list_new = fopen(".wtd/type/typelist", "w+");
    fprintf(fp_type_list_new, "\n");
    char *name = malloc(sizeof(char) * MAX_WTD_NAME_LENGTH);
    while (fscanf(fp_type_list_old, "\n%s", name) != EOF) {
      fprintf(fp_type_list_new, "%s\n", name);
    }
    fprintf(fp_type_list_new, "%s\n", type_name);
    remove(".wtd/type/typelist.old");
    fclose(fp_type_list_new);
    fclose(fp_type_list_old);
    free(name);
    return 0;
  }
  if (MODE == REGISTER_REMOVE_TYPE) {
    rename(".wtd/type/typelist", ".wtd/type/typelist.old");
    FILE *fp_type_list_old = fopen(".wtd/type/typelist.old", "r");
    FILE *fp_type_list_new = fopen(".wtd/type/typelist", "w+");
    fprintf(fp_type_list_new, "\n");
    char *name = malloc(sizeof(char) * MAX_WTD_NAME_LENGTH);
    while (fscanf(fp_type_list_old, "\n%s", name) != EOF) {
      if (!strcmp(name, type_name)) {
        continue;
      }
      fprintf(fp_type_list_new, "%s\n", name);
    }
    remove(".wtd/type/typelist.old");
    fclose(fp_type_list_new);
    fclose(fp_type_list_old);
    free(name);
    return 0;
  }
  return 1;
}