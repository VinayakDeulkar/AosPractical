
// Q.2) Write a C program which create a child process which catch a signal sighup, sigint and sigquit. The Parent process send a sighup or sigint signal after every 3 seconds, at the end of 30 second parent send sigquit signal to child and child terminates my displaying message “My DADDY has Killed me!!!”
// Answer:-
// A signal is a type of notification to a process indicating the occurrence of an event. It is also called the software interrupt and is not predictable to know its occurrence. Thus it is also known as an asynchronous event.
// A signal can be specified with a name or a number; usually, signal names start with SIG.
// To get the signal commands supported by your system, use the “kill -l” (l is for list) command; the following is the list of signal commands.
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

// function declaration of sighup, sigint and sigquit functions
void sighup();
void sigint();
void sigquit();

// main function or driver code
void main()
{
	int pid;
	// pid variable, which will be used later to identify the process, whether it is child process or parent process
	// to get the child process
	if ((pid = fork()) < 0)
	{
		perror("fork");
		exit(1);
	}

	if (pid == 0)
	{	 /* child process, since pid equals to zero for child process */
		signal(SIGHUP, sighup);
		signal(SIGINT, sigint);
		signal(SIGQUIT, sigquit);
		for (;;)
			;   /* infinite loop i.e. loop for ever  */
	}

	else	/* parent process*/
		{ // pid hold the process id of child process
			printf("\nPARENT: sending SIGHUP\n\n");
			kill(pid, SIGHUP);
			sleep(3); // pause for 3 seconds

			printf("\nPARENT: sending SIGINT\n\n");
			kill(pid, SIGINT);
			sleep(3); // pause for 3 seconds
			
			printf("\nPARENT: sending SIGQUIT\n\n");
			kill(pid, SIGQUIT);
			sleep(3); // pause for 3 seconds
		}
}

// function definition of sighup()
void sighup()
{
	signal(SIGHUP, sighup); /* reset signal */
	printf("CHILD: I have received a SIGHUP\n");
}

// function definition of sigint()
void sigint()
{
	signal(SIGINT, sigint); /* reset signal */
	printf("CHILD: I have received a SIGINT\n");
}

// function definition of sigquit()
void sigquit()
{
	printf("My DADDY has Killed me!!!\n");
	exit(0);
}
