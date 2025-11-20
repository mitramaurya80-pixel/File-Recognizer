#include<stdio.h>
#include<stdlib.h>


void create_folder_command(const char *folder_name) {
    char command[256];
    snprintf(command, sizeof(command), "mkdir -p \"%s\"", folder_name);
    system(command);
}