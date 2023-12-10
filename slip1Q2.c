#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
#include <stdlib.h>
void Dingdong()
{
    printf("Ding!");
    exit(1);
}

int main(int argc, char *argv[])
{
    int PauseSecond,i;
    if(argc!=3){
        printf("\n How much seconds you want to sleep the child process\n");
    }
    for(i=0;i<argc;i++){
        PauseSecond=atoi((argv[i]));
        if(fork()==0)
        {
            printf(" \n%d waiting for alarm to go off\n",getpid());
            printf("%d second pause",PauseSecond);
            printf("\n fgf");
            printf("\n");
            sleep(PauseSecond);
            kill(getpid(),SIGALRM);
        }
        else {
            printf("\n %d Alarm application starting\n", getpid());
            signal(SIGALRM,Dingdong);
            printf("\ndone");
        }
    }
}