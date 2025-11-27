#ifndef COMMAND_EXE_H
#define COMMAND_EXE_H

// Function declarations
void execute_command(const char *command);
void create_folder_command(const char *folder_name);
void create_folder_in_home(const char *folder_name);
void move_file_command(const char *source, const char *destination);
void change_directory_command(const char *directory);
void setup_organization_folders();
int directory_exists(const char *path);
char* get_home_directory();
const char* get_platform_name();

#endif
