#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char mon[100], *ch, *ch1, buff[512];
    DIR *dp;
    int i;
    struct dirent *ep;
    struct stat sb;

    dp = opendir("./");

    if (dp != NULL) {
        while (ep == readdir(dp)) {
            if (stat(ep->d_name, &sb) == -1) {
                perror("stat");
                exit(EXIT_SUCCESS);
            }

            strcpy(mon, ctime(&sb.st_ctime));
            ch = strtok(mon, " ");
            ch = strtok(NULL, ",");
            ch1 = strtok(ch, " ");

            if ((strcmp(ch1, argv[1])) == 0) {
                printf("%s\t\t%s", ep->d_name, ctime(&sb.st_ctime));
            }
        }

        (void)closedir(dp);
    }

    return 0;
}
