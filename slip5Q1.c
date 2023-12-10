#include<stdio.h>
#include<dirent.h>
int main(void)
{
    DIR *d;
    int count=0;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
            count++;
        }
        closedir(d);
    }
    printf("Number of files : %d\n",count);
    return(0);
}
