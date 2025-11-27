#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "recognizer.h"
#include "command_exe.h"
#include <dirent.h>
#include <sys/stat.h>

const char *get_file_extension(const char *filename) {
    const char *ext = file_recognizer(filename);
    if(ext == NULL) {
        return "unknown";
    }
    
    // Extended file type checking
    if(strcmp(ext,".png") == 0 || strcmp(ext,".jpg") == 0 || strcmp(ext,".jpeg") == 0 || 
       strcmp(ext,".gif") == 0 || strcmp(ext,".bmp") == 0 || strcmp(ext,".tiff") == 0 || 
       strcmp(ext,".ico") == 0 || strcmp(ext,".psd") == 0 || strcmp(ext,".svg") == 0 ||
       strcmp(ext,".webp") == 0) {
        return ext;
    }
    // Text and documents
    else if(strcmp(ext,".txt") == 0 || strcmp(ext,".pdf") == 0 || strcmp(ext,".doc") == 0 || 
            strcmp(ext,".docx") == 0 || strcmp(ext,".rtf") == 0 || strcmp(ext,".odt") == 0) {
        return ext;
    }
    // Code files
    else if(strcmp(ext,".c") == 0 || strcmp(ext,".cpp") == 0 || strcmp(ext,".h") == 0 ||
            strcmp(ext,".java") == 0 || strcmp(ext,".py") == 0 || strcmp(ext,".js") == 0 ||
            strcmp(ext,".html") == 0 || strcmp(ext,".css") == 0 || strcmp(ext,".xml") == 0 ||
            strcmp(ext,".php") == 0 || strcmp(ext,".rb") == 0) {
        return ext;
    }
    // Audio files
    else if(strcmp(ext,".mp3") == 0 || strcmp(ext,".wav") == 0 || strcmp(ext,".flac") == 0 || 
            strcmp(ext,".ogg") == 0 || strcmp(ext,".m4a") == 0 || strcmp(ext,".aac") == 0) {
        return ext;
    }
    // Video files
    else if(strcmp(ext,".mp4") == 0 || strcmp(ext,".avi") == 0 || strcmp(ext,".mkv") == 0 || 
            strcmp(ext,".mov") == 0 || strcmp(ext,".wmv") == 0 || strcmp(ext,".flv") == 0 ||
            strcmp(ext,".webm") == 0) {
        return ext;
    }
    // Archives
    else if(strcmp(ext,".zip") == 0 || strcmp(ext,".tar") == 0 || strcmp(ext,".gz") == 0 || 
            strcmp(ext,".rar") == 0 || strcmp(ext,".7z") == 0 || strcmp(ext,".bz2") == 0) {
        return ext;
    }
    // Spreadsheets
    else if(strcmp(ext,".xls") == 0 || strcmp(ext,".xlsx") == 0 || strcmp(ext,".csv") == 0 ||
            strcmp(ext,".ods") == 0) {
        return ext;
    }
    // Presentations
    else if(strcmp(ext,".ppt") == 0 || strcmp(ext,".pptx") == 0 || strcmp(ext,".odp") == 0) {
        return ext;
    }
    // Executables
    else if(strcmp(ext,".exe") == 0 || strcmp(ext,".msi") == 0 || strcmp(ext,".app") == 0 ||
            strcmp(ext,".deb") == 0 || strcmp(ext,".rpm") == 0) {
        return ext;
    }
    // Fonts
    else if(strcmp(ext,".ttf") == 0 || strcmp(ext,".otf") == 0 || strcmp(ext,".woff") == 0 || 
            strcmp(ext,".woff2") == 0) {
        return ext;
    }
    // Databases
    else if(strcmp(ext,".sqlite") == 0 || strcmp(ext,".db") == 0 || strcmp(ext,".mdb") == 0) {
        return ext;
    }
    else {
        return "unknown";
    }
}

void organize_file_by_type(const char *filename) {
    const char *extension = get_file_extension(filename);
    
    if(extension != NULL && strcmp(extension, "unknown") != 0) {
        printf("Processing file: %s (Type: %s)\n", filename, extension);
        
        char dest_folder[256];
        char dest_path[512];
        char *home = get_home_directory();
        
        // Determine destination folder based on file type
        if(strcmp(extension, ".png") == 0 || strcmp(extension, ".jpg") == 0 || 
           strcmp(extension, ".jpeg") == 0 || strcmp(extension, ".gif") == 0 || 
           strcmp(extension, ".bmp") == 0 || strcmp(extension, ".tiff") == 0 || 
           strcmp(extension, ".ico") == 0 || strcmp(extension, ".psd") == 0 ||
           strcmp(extension, ".svg") == 0 || strcmp(extension, ".webp") == 0) {
            strcpy(dest_folder, "Images");
        }
        else if(strcmp(extension, ".mp3") == 0 || strcmp(extension, ".wav") == 0 || 
                strcmp(extension, ".flac") == 0 || strcmp(extension, ".ogg") == 0 ||
                strcmp(extension, ".m4a") == 0 || strcmp(extension, ".aac") == 0) {
            strcpy(dest_folder, "Music");
        }
        else if(strcmp(extension, ".mp4") == 0 || strcmp(extension, ".avi") == 0 || 
                strcmp(extension, ".mkv") == 0 || strcmp(extension, ".mov") == 0 ||
                strcmp(extension, ".wmv") == 0 || strcmp(extension, ".flv") == 0 ||
                strcmp(extension, ".webm") == 0) {
            strcpy(dest_folder, "Videos");
        }
        else if(strcmp(extension, ".txt") == 0 || strcmp(extension, ".pdf") == 0 || 
                strcmp(extension, ".doc") == 0 || strcmp(extension, ".docx") == 0 ||
                strcmp(extension, ".rtf") == 0 || strcmp(extension, ".odt") == 0) {
            strcpy(dest_folder, "Documents");
        }
        else if(strcmp(extension, ".c") == 0 || strcmp(extension, ".cpp") == 0 || 
                strcmp(extension, ".h") == 0 || strcmp(extension, ".java") == 0 ||
                strcmp(extension, ".py") == 0 || strcmp(extension, ".js") == 0 ||
                strcmp(extension, ".html") == 0 || strcmp(extension, ".css") == 0 ||
                strcmp(extension, ".xml") == 0 || strcmp(extension, ".php") == 0 ||
                strcmp(extension, ".rb") == 0) {
            strcpy(dest_folder, "Code");
        }
        else if(strcmp(extension, ".zip") == 0 || strcmp(extension, ".tar") == 0 || 
                strcmp(extension, ".gz") == 0 || strcmp(extension, ".rar") == 0 ||
                strcmp(extension, ".7z") == 0 || strcmp(extension, ".bz2") == 0) {
            strcpy(dest_folder, "Archives");
        }
        else if(strcmp(extension, ".xls") == 0 || strcmp(extension, ".xlsx") == 0 || 
                strcmp(extension, ".csv") == 0 || strcmp(extension, ".ods") == 0) {
            strcpy(dest_folder, "Spreadsheets");
        }
        else if(strcmp(extension, ".ppt") == 0 || strcmp(extension, ".pptx") == 0 || 
                strcmp(extension, ".odp") == 0) {
            strcpy(dest_folder, "Presentations");
        }
        else if(strcmp(extension, ".exe") == 0 || strcmp(extension, ".msi") == 0 || 
                strcmp(extension, ".app") == 0 || strcmp(extension, ".deb") == 0 ||
                strcmp(extension, ".rpm") == 0) {
            strcpy(dest_folder, "Executables");
        }
        else if(strcmp(extension, ".ttf") == 0 || strcmp(extension, ".otf") == 0 || 
                strcmp(extension, ".woff") == 0 || strcmp(extension, ".woff2") == 0) {
            strcpy(dest_folder, "Fonts");
        }
        else if(strcmp(extension, ".sqlite") == 0 || strcmp(extension, ".db") == 0 || 
                strcmp(extension, ".mdb") == 0) {
            strcpy(dest_folder, "Databases");
        }
        else {
            strcpy(dest_folder, "Other");
        }
        
        // Create folder in home directory if it doesn't exist
        create_folder_in_home(dest_folder);
        
        // Build destination path in home directory
        #ifdef _WIN32
            snprintf(dest_path, sizeof(dest_path), "%s\\%s\\%s", home, dest_folder, filename);
        #else
            snprintf(dest_path, sizeof(dest_path), "%s/%s/%s", home, dest_folder, filename);
        #endif
        
        // Move file to home directory folder
        move_file_command(filename, dest_path);
        
    } else {
        printf("Unknown file type or cannot read: %s\n", filename);
        
        // Move unknown files to "Other" folder in home directory
        char dest_path[512];
        char *home = get_home_directory();
        create_folder_in_home("Other");
        #ifdef _WIN32
            snprintf(dest_path, sizeof(dest_path), "%s\\Other\\%s", home, filename);
        #else
            snprintf(dest_path, sizeof(dest_path), "%s/Other/%s", home, filename);
        #endif
        move_file_command(filename, dest_path);
    }
}

int main(){
    // Setup organization folders in home directory
    setup_organization_folders();
    
    // Platform-specific default directories
    const char *downloads_dir;
#ifdef _WIN32
    downloads_dir = getenv("USERPROFILE");
    if (downloads_dir) {
        char win_downloads[512];
        snprintf(win_downloads, sizeof(win_downloads), "%s\\Downloads", downloads_dir);
        change_directory_command(win_downloads);
    }
#elif __APPLE__
    downloads_dir = getenv("HOME");
    if (downloads_dir) {
        char mac_downloads[512];
        snprintf(mac_downloads, sizeof(mac_downloads), "%s/Downloads", downloads_dir);
        change_directory_command(mac_downloads);
    }
#else
    // Linux - Get the current user's home directory dynamically
    downloads_dir = getenv("HOME");
    if (downloads_dir) {
        char linux_downloads[512];
        snprintf(linux_downloads, sizeof(linux_downloads), "%s/Downloads", downloads_dir);
        change_directory_command(linux_downloads);
    } else {
        // Fallback if HOME is not set
        printf("Warning: HOME environment variable not set. Using current directory.\n");
    }
#endif
    
    printf("Platform: %s\n", get_platform_name());
    printf("Current directory: ");
    system("pwd"); // Show current directory
    printf("Starting file organization...\n");
    
    // Read ALL files in current directory
    DIR *dir;
    struct dirent *entry;
    
    dir = opendir(".");
    if (dir == NULL) {
        perror("Cannot open current directory");
        return 1;
    }
    
    int file_count = 0;
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        
        // Skip if it's a directory
        struct stat file_stat;
        if (stat(entry->d_name, &file_stat) == 0 && S_ISDIR(file_stat.st_mode)) {
            continue;
        }
        
        // Process the file
        printf("\nProcessing: %s\n", entry->d_name);
        organize_file_by_type(entry->d_name);
        file_count++;
    }
    
    closedir(dir);
    
    printf("\nFile organization completed! Processed %d files.\n", file_count);
    return 0;
}
