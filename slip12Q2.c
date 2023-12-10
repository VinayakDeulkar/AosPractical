
// Q.2) Write a C program which receives file names as command line arguments and display those filenames in ascending order according to their sizes. I) (e.g $ a.out a.txt b.txt c.txt, …)
// Answer:-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Structure to hold file information
struct FileInfo {
    char name[256];
    off_t size;
};

// Function to compare two FileInfo structures based on size
int compareFileSize(const void *a, const void *b) {
    return ((struct FileInfo *)a)->size - ((struct FileInfo *)b)->size;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file1 file2 file3 ...\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create an array of FileInfo structures
    struct FileInfo fileInfos[argc - 1];

    // Collect file information
    for (int i = 1; i < argc; i++) {
        strncpy(fileInfos[i - 1].name, argv[i], sizeof(fileInfos[i - 1].name) - 1);
        fileInfos[i - 1].name[sizeof(fileInfos[i - 1].name) - 1] = '\0';  // Ensure null-termination

        struct stat fileStat;
        if (stat(argv[i], &fileStat) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        fileInfos[i - 1].size = fileStat.st_size;
    }

    // Sort the array of FileInfo structures based on size
    qsort(fileInfos, argc - 1, sizeof(struct FileInfo), compareFileSize);

    // Display the sorted filenames and their sizes
    printf("File names sorted by size:\n");
    for (int i = 0; i < argc - 1; i++) {
        printf("%s: %ld bytes\n", fileInfos[i].name, (long)fileInfos[i].size);
    }

    return 0;
}