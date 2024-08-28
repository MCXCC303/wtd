#include "builtin.h"
#include <dirent.h>
#include <stdio.h>

int cmd_remove(int argc, const char **argv) {
  if (WTD_NOT_EXIST) {
    printf("No wtd detected.\n");
    return 0;
  }
  char *wtd_name = get_wtd_name();
  printf("Detected existed to-do list named \"%s\".\nDelete \"%s\"? [y/N] ",
         wtd_name, wtd_name);
  if (getchar() == 'y') {
    delete_directory(".wtd/");
    printf("wtd named \"%s\" has been removed successfully.\n", wtd_name);
    return 0;
  }
  printf("Aborted.\n");
  return 0;
}