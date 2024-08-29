#include "builtin.h"

struct cmd_struct td_commands[] = {
    {"add", cmd_td_add}, {"show", cmd_td_show}, {"remove", cmd_td_remove}};

int cmd_td(int argc, const char **argv) { return 0; }

int cmd_td_add(int argc, const char **argv) { return 0; };
int cmd_td_remove(int argc, const char **argv) { return 0; };
int cmd_td_show(int argc, const char **argv) { return 0; };