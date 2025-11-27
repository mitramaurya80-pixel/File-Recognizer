#include<stdio.h>
#include<stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#else
#include <pwd.h>
#endif

// Function to detect current platform
const char* get_platform_name() {
    #ifdef _WIN32
        return "Windows";
    #elif __APPLE__
        return "macOS";
    #elif __linux__
        return "Linux";
    #else
        return "Unknown";
    #endif
}

// Function to check if directory exists
int directory_exists(const char *path) {
    struct stat st;
    return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

// Function to get home directory path (cross-platform)
char* get_home_directory() {
    static char home_path[512];
    
    #ifdef _WIN32
        // Windows
        if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_PROFILE, NULL, 0, home_path))) {
            return home_path;
        }
    #else
        // Unix-like systems (Linux, macOS)
        char *home = getenv("HOME");
        if (home != NULL) {
            strncpy(home_path, home, sizeof(home_path));
            return home_path;
        }
        
        // Fallback for Unix systems
        struct passwd *pw = getpwuid(getuid());
        if (pw != NULL) {
            strncpy(home_path, pw->pw_dir, sizeof(home_path));
            return home_path;
        }
    #endif
    
    // Final fallback
    strcpy(home_path, ".");
    return home_path;
}

// Cross-platform execute command
void execute_command(const char *command) {
    printf("Executing: %s\n", command);
    int result = system(command);
    if (result != 0) {
        printf("Command failed with code: %d\n", result);
    }
}

// Cross-platform folder creation
void create_folder_command(const char *folder_name) {
    // Check if folder already exists in current directory
    if (directory_exists(folder_name)) {
        printf("Folder '%s' already exists in current directory\n", folder_name);
        return;
    }
    
    char command[256];
    #ifdef _WIN32
        snprintf(command, sizeof(command), "mkdir \"%s\"", folder_name);
    #else
        snprintf(command, sizeof(command), "mkdir -p \"%s\"", folder_name);
    #endif
    execute_command(command);
}

// Cross-platform folder creation in home directory
void create_folder_in_home(const char *folder_name) {
    char home_path[512];
    char *home = get_home_directory();
    snprintf(home_path, sizeof(home_path), "%s/%s", home, folder_name);
    
    // Check if folder already exists in home directory
    if (directory_exists(home_path)) {
        printf("Folder '%s' already exists in home directory\n", folder_name);
        return;
    }
    
    char command[256];
    #ifdef _WIN32
        snprintf(command, sizeof(command), "mkdir \"%s\"", home_path);
    #else
        snprintf(command, sizeof(command), "mkdir -p \"%s\"", home_path);
    #endif
    execute_command(command);
    printf("Created folder: %s\n", home_path);
}

// Cross-platform file movement
void move_file_command(const char *source, const char *destination) {
    // Check if source file exists
    struct stat st;
    if (stat(source, &st) != 0) {
        printf("Source file '%s' does not exist\n", source);
        return;
    }
    
    char command[512];
    #ifdef _WIN32
        // Windows: use move command
        snprintf(command, sizeof(command), "move \"%s\" \"%s\"", source, destination);
    #else
        // Unix-like: copy and remove
        snprintf(command, sizeof(command), "cp \"%s\" \"%s\"", source, destination);
        execute_command(command);
        snprintf(command, sizeof(command), "rm \"%s\"", source);
    #endif
    execute_command(command);
    printf("Moved file: %s -> %s\n", source, destination);
}

// Cross-platform directory change
void change_directory_command(const char *directory) {
    #ifdef _WIN32
        if (SetCurrentDirectory(directory) == 0) {
            printf("Failed to change directory to: %s\n", directory);
        }
    #else
        if (chdir(directory) != 0) {
            perror("chdir failed");
        }
    #endif
}

// Function to check and create all necessary folders in home directory
void setup_organization_folders() {
    const char *folders[] = {
        "Documents", "Images", "Videos", "Music", "Archives", 
        "TextFiles", "Code", "Executables", "Spreadsheets", "Presentations",
        "Fonts", "Databases", "Other"
    };
    int num_folders = sizeof(folders) / sizeof(folders[0]);
    
    printf("Platform: %s\n", get_platform_name());
    printf("Home directory: %s\n", get_home_directory());
    printf("Setting up organization folders in home directory...\n");
    
    for (int i = 0; i < num_folders; i++) {
        create_folder_in_home(folders[i]);
    }
    printf("Folder setup completed!\n");
} 
