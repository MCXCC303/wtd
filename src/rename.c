/*
  wtd rename command

  Copyright (C) 2024 MCXCC
*/

#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int cmd_rename(int argc, const char **argv) {
  char *old_wtd_name = malloc(sizeof(char) * MAX_WTD_NAME_LENGTH);
  char *init_time = malloc(sizeof(char) * 256);
  struct tm *rename_time = get_current_time();

  if ((argv[2] == NULL) | ((argv[2] != NULL) && !strcmp(argv[2], "-h"))) {
    printf("Usage: wtd rename [-h | --help] [new name]\n");
    return 0;
  }

  if (WTD_NOT_EXIST) {
    printf("No wtd detected.\nUse \"wtd init\" to create one first.\n");
    return 0;
  }

  if (!access(".wtd/conf/wtd.cfg.old", F_OK)) {
    remove(".wtd/conf/wtd.conf.old");
  }

  FILE *fpr = fopen(".wtd/conf/wtd.cfg", "r");
  fscanf(fpr, "name=%s", (char *)old_wtd_name);
  fscanf(fpr, "\ninit_time=%s\n", (char *)init_time);
  fclose(fpr);
  rename(".wtd/conf/wtd.cfg", ".wtd/conf/wtd.cfg.old");

  FILE *fpw = fopen(".wtd/conf/wtd.cfg", "w+");
  fprintf(fpw, "name=%s\n", argv[2]);
  fprintf(fpw, "init_time=%s\n", init_time);
  fprintf(fpw, "rename_time_latest=%d/%d/%d\n", rename_time->tm_year,
          rename_time->tm_mon, rename_time->tm_mday);
  fclose(fpw);

  printf("Renamed wtd from \"%s\" to \"%s\".\n", old_wtd_name, argv[2]);
  free(old_wtd_name);
  free(init_time);
  return 0;
}