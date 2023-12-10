#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;

    // Replace "2023-01" with the desired year and month in "YYYY-MM" format
    const char *targetMonth = "2023-01";

    dir = opendir(".");

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Ignore "." and ".." entries
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Get file information
        if (stat(entry->d_name, &fileStat) < 0) {
            perror("Error getting file information");
            closedir(dir);
            return 1;
        }

        // Extract year and month from the creation time
        struct tm *creationTime = localtime(&fileStat.st_ctime);
        char fileMonth[8];
        strftime(fileMonth, sizeof(fileMonth), "%Y-%m", creationTime);

        // Compare the target month
        if (strcmp(fileMonth, targetMonth) == 0) {
            printf("%s\n", entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}
