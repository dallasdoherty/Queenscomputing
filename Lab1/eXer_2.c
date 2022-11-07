/******************************************************************************
Dallas Doherty
20220683

2.1:
Since two child process are running at the same instance and executing the same
piece of code and the output is dependent on the order of execution of the processes
they are overwriting each other.

2.2:
5000, if all the child processes fail, the parent process will still execute then
the lowest possible n is 5000.
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <wait.h>
#include <stdlib.h>


int main ()
{
	pid_t pid_0, pid_1, pid_2, pid_3;
	int status;

	//The parent process creates a child process
	pid_1 = fork();
	wait(&status) //2.3
	//The parent process tests whether fork() failed or not, if it did, the process exits.
	if (pid_1 < 0)  goto X;

        //The parent process creates a child process
        if(pid_1 != 0) pid_2 = fork();
        wait(&status) // 2.3
        //The parent process tests whether fork() failed or not, if it did, the process exits.
        if ((pid_1 != 0) && (pid_2 < 0))  goto X;

	//The parent process creates a child process
        if((pid_1 != 0) && (pid_2 != 0)) pid_3 = fork();
        wait(&status) //2.3
        //The parent process tests whether fork() failed or not, if it did, the process exits.
        if ((pid_1 != 0) && (pid_2 != 0) && (pid_3 < 0))  goto X;


	if(pid_1==0 || pid_2==0 || pid_3==0) 		//Child processes execute this segment of code
	{
		//Process executes another program (Make sure to indicate the complete path of your program count.out in the "X"-field
		//and the name of the executable file in the "Y"-field e.g., replace "X" with "/home/xyz/Desktop/Lab1/count.out" and "Y" with "./count.c"
		//E.g., in my case it is: execl("/home/karim/Desktop/Labs/L1/count.out","./count.out", NULL);
		execl("/Users/dallas/Documents/CISC324/Lab1/count.out","./count.c", NULL);
		//prints to user that execl failed
		printf("Process[%d]: Failed to execute execl()\n",getpid());
	}
	else 		//Parent process execute this segment of code
	{

		printf("Parent process waiting for its children to terminate ...\n");
                //Parent process waits for the first child that terminates and displays its termination status (1 normally, 0 abnormally) along with its PID
		pid_0 = wait(&status);
		printf("Parent[%d]: child %d has terminated (status=%d)\n",getpid(),pid_0,WIFEXITED(status));
		//Parent process waits for the second child that terminates and displays its termination status (1 normally, 0 abnormally) along with its PID
		pid_0 = wait(&status);
                printf("Parent[%d]: child %d has terminated (status=%d)\n",getpid(),pid_0, WIFEXITED(status));
		//Parent process waits for the third child that terminates and displays its termination status (1 normally, 0 abnormally) along with its PID
		pid_0 = wait(&status);
                printf("Parent[%d]: child %d has terminated (status=%d)\n",getpid(),pid_0, WIFEXITED(status));
		//parent process sleeps for 1 second to give time to its child processes to display their outputs.
		sleep(1);
		printf("Parent process terminated.\n");


	}


X: return 0;

}
