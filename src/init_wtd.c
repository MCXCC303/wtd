#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int cmd_init(int argc, const char **argv) {
  const char *init_wtd_name = argv[2] == NULL ? "default" : argv[2];
  struct tm *time_struct = get_current_time();

  if (argv[2] != NULL &&
      (!strcmp(argv[2], "-h") | !strcmp(argv[2], "--help"))) {
    printf("Usage: wtd init [-h | --help] [name]\n");
    return 0;
  }

  if (DETECTED_WTD) {
    char *exist_wtd_name = get_wtd_name();
    printf("Already existed to-do list named \"%s\".\n"
           "Use \"wtd rename\" to rename this to-do list.\n",
           exist_wtd_name);
    return 0;
  }

  mkdir(".wtd", 0755);
  mkdir(".wtd/conf", 0755);
  mkdir(".wtd/type", 0755);
  FILE *fp = fopen(".wtd/conf/wtd.cfg", "w+");
  fprintf(fp, "name=%s\n", init_wtd_name);
  fprintf(fp, "init_time=%d/%d/%d\n", time_struct->tm_year, time_struct->tm_mon,
          time_struct->tm_mday);
  fclose(fp);
  FILE *fp_type_list = fopen(".wtd/type/typelist", "w+");
  fprintf(fp_type_list, "\n");
  fclose(fp_type_list);
  printf("Initiate to-do list named \"%s\".\n", init_wtd_name);
  return 0;
}