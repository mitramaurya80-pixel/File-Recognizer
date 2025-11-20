#include <stdio.h>
#include <string.h>

const char *get_os(void) {
#if defined(_WIN32) || defined(_WIN64)
    return "windows";
#elif defined(__linux__)
    return "linux";
#elif defined(__APPLE__)
    return "macOS";
#else
    return NULL;
#endif
}

int main(void) {
    const char *os = get_os();
    if (!os) {
        printf("Unknown OS\n");
        return 1;
    }

    if (strcmp(os, "linux") == 0) {
        printf("This is linux OS\n");
    } else if (strcmp(os, "windows") == 0) {
        printf("This is windows OS\n");
    } else if (strcmp(os, "macOS") == 0) {
        printf("This is macOS\n");
    } else {
        printf("OS: %s\n", os);
    }
    return 0;
}